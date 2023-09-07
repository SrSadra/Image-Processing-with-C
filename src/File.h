#include <stdio.h>
#include <stdlib.h>

//whithout curl (just can handle image content types)
#include <winsock2.h>
#include <string.h>
#include <openssl/err.h>

//can handle all types of files
#include <curl/curl.h>

//for getting random number as file names
#include <time.h>

#pragma comment(lib, "libssl.lib");
#pragma comment(lib, "libcrypto.lib");

#define MAX_FILE_NAME 400
#define MAX_REQUEST_SIZE 2048
#define BUFFER_SIZE 5000

#define STB_IMAGE_IMPLEMENTATION
#include "lib/write/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/write/stb_image_write.h"




unsigned char* readBMPImage(const char* filename , int* width , int* height , int* channels) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    // Seek to the start of image data offset
    fseek(file, 10, SEEK_SET);
    unsigned char imageDataOffset[4];
    fread(imageDataOffset, sizeof(unsigned char), 4, file);
    int dataOffset = *(int*)imageDataOffset;

    // Seek to the image width offset
    fseek(file, 18, SEEK_SET);
    unsigned char imageWidth[4];
    fread(imageWidth, sizeof(unsigned char), 4, file);
    int widthTmp = *(int*)imageWidth;

    // Seek to the image height offset
    fseek(file, 22, SEEK_SET);
    unsigned char imageHeight[4];
    fread(imageHeight, sizeof(unsigned char), 4, file);
    int heightTmp = *(int*)imageHeight;

    // Seek to the image color depth offset
    fseek(file, 28, SEEK_SET);
    unsigned char imageColorDepth[2];
    fread(imageColorDepth, sizeof(unsigned char), 2, file);
    int colorDepth = *(short*)imageColorDepth;

    // Calculate the number of color channels
    int channelsTmp = colorDepth / 8;

    // Calculate the image size
    fseek(file, 34, SEEK_SET);
    unsigned char imageSizeBytes[4];
    fread(imageSizeBytes, sizeof(unsigned char), 4, file);
    int imageSize = *(int*)imageSizeBytes;

    // Allocate memory for image data
    unsigned char* imageData = (unsigned char*)malloc(imageSize);
    if (imageData == NULL) {
        printf("Failed to allocate memory for image data\n");
        fclose(file);
        return NULL;
    }

    // Read image data
    fseek(file, dataOffset, SEEK_SET);
    fread(imageData, sizeof(unsigned char), imageSize, file);

    // Close the file
    fclose(file);


    *width = widthTmp;
    *height = heightTmp;
    *channels = channelsTmp;

    return imageData;
}

unsigned char* readfile(int* width , int* height  , int* channels , char* path , char* format){
    if (!strcmp(format , "png")){
        return stbi_load(path, width, height, channels, 0);
    }
    else if (!strcmp(format , "jpg")){
        return stbi_load(path, width, height, channels, STBI_rgb);
    }
    else if (!strcmp(format , "bm")){
        return readBMPImage(path , width , height , channels);
    }
    else{
        printf("Error reading the image");
        return NULL;
    }
}



int downloadImage(const char* url, const char* file) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    // Extract the server hostname and path from the URL
    char hostname[MAX_FILE_NAME];
    char path[MAX_FILE_NAME];
    if (sscanf(url, "http://%99[^/]/%199[^\n]", hostname, path) != 2 &&
        sscanf(url, "https://%99[^/]/%199[^\n]", hostname, path) != 2) {
        printf("Invalid URL\n");
        WSACleanup();
        return 2;
    }

    // Resolve the server hostname
    struct hostent* host = gethostbyname(hostname);
    if (host == NULL) {
        printf("Failed to resolve hostname\n");
        WSACleanup();
        return 3;
    }

    // Create a TCP socket
    SOCKET socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == INVALID_SOCKET) {
        printf("Failed to create socket\n");
        WSACleanup();
        return 4;
    }

    // Connect to the server
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);  // HTTP port
    serverAddress.sin_addr.s_addr = *(unsigned long*)host->h_addr;

    if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Failed to connect to the server\n");
        closesocket(socketFD);
        WSACleanup();
        return 5;
    }

    // Send an HTTP GET request
    char request[MAX_REQUEST_SIZE];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, hostname);
    printf("request: %s\n", request);
    if (send(socketFD, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Failed to send HTTP request\n");
        closesocket(socketFD);
        WSACleanup();
        return 6;
    }

    // Receive the server's response
    char buffer[BUFFER_SIZE];
    int bytesRead;
    int headerEnd = 0;
    FILE* outputFile = fopen(file, "w+b");
    printf("Downloading...\n");
    while ((bytesRead = recv(socketFD, buffer, BUFFER_SIZE, 0)) > 0) {
        if (!headerEnd) {
            printf("%s\n", buffer);
            // Search for the end of the header
            char* headerEndMarker = "\r\n\r\n";
            char* headerEndPos = strstr(buffer, headerEndMarker);
            if (headerEndPos != NULL) {
                // Write the remaining data after the header to the output file
                int headerSize = headerEndPos - buffer + strlen(headerEndMarker);
                fwrite(buffer + headerSize, 1, bytesRead - headerSize, outputFile);
                headerEnd = 1;
            }
        } else {
            // Write the received data to the output file
            if (strstr(buffer, "Content-Type: text/html") != NULL) {
                // Handle text data
                fputs(buffer, outputFile);
            } else {
                // Handle binary data
                fwrite(buffer, 1, bytesRead, outputFile);
            }
        }
    }
    // Close the output file and the socket
    fclose(outputFile);
    closesocket(socketFD);
    WSACleanup();

    printf("File downloaded successfully\n");

    return 0;
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

char* setDownloadedName(const char* url){
    char* path = "Data\\downloaded\\";
    char* tmp = (char*) malloc(1000);
    srand(time(0));
    int randnum = rand();
    char arr[10];
    sprintf(arr , "%d", randnum);
    strcpy(tmp , path);
    strcat(tmp , arr);
    printf("%s", tmp);
    char* format = strrchr(url , '.');
    strcat(tmp , format);
    printf("%s", tmp);
    return tmp;
}


int download_image(const char *url , char** filename) {
    CURL *curl;
    FILE *file;
    CURLcode res;
    *filename = setDownloadedName(url);
    printf("\n\n%s", *filename);
    curl = curl_easy_init();
    printf("Downloading...");
    if (curl) {
        printf("---%s\n", *filename);
        file = fopen(*filename, "ab+");
        if (file) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                printf("Failed to download: %s\n", curl_easy_strerror(res));
                fclose(file);
                curl_easy_cleanup(curl);
                return 1;
            }

            fclose(file);
        } else {
            printf("Failed to open file: %s\n", *filename);
            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    } else {
        printf("Failed to initialize libcurl\n");
        return 1;
    }

    return 0;
}
