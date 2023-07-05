#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <ws2tcpip.h>
#include <curl/curl.h>


#define MAX_BUFFER_SIZE 60000

// #include <windows.h>
// #include <sys/types.h>

// #include "stb_image/inet.h"
// #include <unistd.h>
// #include <netinet/in.h>
// #include "stb_image/in.h"


#define STB_IMAGE_IMPLEMENTATION
#include "lib/write/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/write/stb_image_write.h"

#define bufferSize 1000


// #pragma comment(lib, "ws2_32.lib")

// void initialize(int type){

// }

//size_t write_callback(void* ptr, size_t size, size_t nmemb, FILE* stream) {
//    return fwrite(ptr, size, nmemb, stream);
//}

unsigned char* readfile(int* width , int* height  , int* channels , char* path , char* format){
    unsigned char* image = (unsigned char*) malloc(10000000 * sizeof(char));
    if (!strcmp(format , "png")){
        image = stbi_load(path, width, height, channels, STBI_rgb_alpha);
    }
    else if (!strcmp(format , "jpg")){
        image = stbi_load(path, width, height, channels, STBI_rgb);
    }
    if (image == NULL){
        printf("Error reading the image");
        return NULL;
    }
//    // Calculate the size of each image row
//    size_t rowSize = (*width) * (*channels);
//
//    // Temporary row buffer for flipping
//    unsigned char* rowBuffer = (unsigned char*)malloc(rowSize);
//
//    for (int y = 0; y < (*height) / 2; y++) {
//        unsigned char* topRow = image + y * rowSize;
//        unsigned char* bottomRow = image + ((*height) - y - 1) * rowSize;
//
//        // Swap rows pixel-by-pixel
//        for (int x = 0; x < (*width); x++) {
//            unsigned char* topPixel = topRow + x * (*channels);
//            unsigned char* bottomPixel = bottomRow + x * (*channels);
//
//            // Swap pixel values
//            for (int c = 0; c < (*channels); c++) {
//                unsigned char temp = topPixel[c];
//                topPixel[c] = bottomPixel[c];
//                bottomPixel[c] = temp;
//            }
//        }
//    }
//
//    free(rowBuffer);

    return image;
}


// Function to download the image from the specified URL
unsigned char* downloadImage(const char* url, int* width, int* height, int* channels) {
    unsigned char* imageData = NULL;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Failed to initialize Winsock");
        return NULL;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return NULL;
    }

    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const char* domain = strstr(url, "//");
    if (domain != NULL) {
        domain += 2;
    } else {
        domain = url;
    }
    printf("%s\n", domain);
    struct hostent* server = gethostbyname("www.simplilearn.com");
    if (server == NULL) {
        printf("Failed to resolve host\n");
        closesocket(sockfd);
        WSACleanup();
        return NULL;
    }
    printf("mishe?");
    // Prepare server address structure
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(443);
    memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);
    printf("shod?");
    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Failed to connect to server\n");
        closesocket(sockfd);
        WSACleanup();
        return NULL;
    }
    printf("fek konam");
    char request[MAX_BUFFER_SIZE];
    sprintf(request, "GET %s HTTP/1.1\\r\\nHost: %s\\r\\nUser-Agent: Mozilla/5.0\\r\\nConnection: close\\r\\n\\r\\n",  "/ice9/free_resources_article_thumb/what_is_image_Processing.jpg" , "www.simplilearn.com");
    if (send(sockfd, request, (int)strlen(request), 0) == SOCKET_ERROR) {
        perror("Send request failed");
        freeaddrinfo(res);
        closesocket(sockfd);
        WSACleanup();
        return NULL;
    }

    // Receive the image data
    int totalBytesRead = 0; // it contains http headers , html content and...
    char buffer[MAX_BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0)) > 0) {
        imageData = realloc(imageData, totalBytesRead + bytesRead);
        if (!imageData) {
            printf("Memory allocation failed\n");
            closesocket(sockfd);
            WSACleanup();
            return NULL;
        }
        memcpy(imageData + totalBytesRead, buffer, bytesRead);
        totalBytesRead += bytesRead;
        printf("%d\n", totalBytesRead);
        // Check if image information is obtained
        if (*width == 0 && *height == 0 && *channels == 0) {
            int tempWidth, tempHeight, tempChannels;
            stbi_uc* imageTempData = stbi_load_from_memory(imageData, totalBytesRead, &tempWidth, &tempHeight, &tempChannels, 0);
            printf("alooo12");
            if (imageTempData != NULL) {
                printf("vaghean");
                *width = tempWidth;
                *height = tempHeight;
                *channels = tempChannels;
            }
        }
    }

    closesocket(sockfd);
    WSACleanup();

    for (int i = 0 ; i < totalBytesRead ; i++){
        printf("%c", imageData[i]);
    }

    if (totalBytesRead == 0) {
        printf("Failed to download image\n");
        free(imageData);
        return NULL;
    }

    return imageData;
}








unsigned char* download_image(const char* url, const char* filename , int* width , int* height , int* channels) {// with https://
//    FILE* file = fopen(filename, "wb");
//    if (!file) {
//        printf("Failed to open the file for writing.\n");
//        return;
//    }
    // Create the command to download the image using curl
    char command[1024];

    snprintf(command, sizeof(command), "curl -o \"%s\" \"%s\"", filename, url);
    // Execute the command using the system function
    int result = system(command);
    printf("%d", result);
    if (result == 0) {
        printf("Image downloaded successfully.\n");
    } else {
        printf("Failed to download the image.\n");
    }

//    fclose(file);
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open the file for reading.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("size %d", size);
    unsigned char* buffer = (unsigned char*)malloc(size);
    if (!buffer) {
        printf("Failed to allocate memory for buffer.\n");
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, size, file) != size) {
        printf("Failed to read the file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    fclose(file);
    remove("temp_image.jpg");

    int temp_width, temp_height, temp_channels;
    unsigned char* image_data = stbi_load_from_memory(buffer, size, &temp_width, &temp_height, &temp_channels, 0);
    if (!image_data) {
        printf("Failed to decode the image.\n");
        free(buffer);
        return NULL;
    }

    *width = temp_width;
    *height = temp_height;
    *channels = temp_channels;

    return image_data;
}


//void readUrl(const char* url){
//    // int sock;
//    // struct sockaddr_in server;
//    // int port = 3030; //?
//    // if ((sock = socket(AF_INET , SOCK_STREAM , 0)) < 0){
//    //     perror("socket can not be created");
//    //     return -1;
//    // }
//    // memset(&server , 0 , sizeof(server));
//    // server.sin_family = AF_INET;
//    // server.sin_port = htons(port); // convert port 16 bit integer to network byte
//
//    // if (inet_pton(AF_INET , url , &(server.sin_addr)) <= 0){
//    //     perror("can not convert !!");
//    //     return -2;
//    // }
//
//    // if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
//    // perror("can not convert");
//    // return -3;
//    // }
//
//    // char* request = "GET /dk-find-out/image/upload/q_80,w_1920,f_auto/MA_00600259_vpf1m0.jpg HTTP/1.1\r\n"
//    //            "Host: cloudinary.com\r\n"
//    //            "\r\n";
//
//    // if (send(sock, request, strlen(request), 0) < 0) {
//    // perror("can't send request!");
//    // return -4;
//    // }
//
//    // char buffer[bufferSize];
//    // int byteRecieved;
//    // FILE *imageF; // file that image is stored to
//    // char* fileN = ""; // the destination
//
//
//    // imageF = fopen(fileN ,"wb");
//    // if (imageF == NULL){
//    //     perror("image file can't be opened");
//    // }
//
//    // while ((byteRecieved = recv(sock, buffer, bufferSize, 0)) > 0) {
//    //     fwrite(buffer, sizeof(char), byteRecieved, imageF);
//    // }
//
//    // fclose(imageF); // fclose for closing file
//    // close(socket); // close for closing socket (input is int)
//
//
//
//
//
//
//
//
//
//
//
//
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        fprintf(stderr, "Failed to initialize Winsock");
//        exit(EXIT_FAILURE);
//    }
//
//    // Create socket
//    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd == INVALID_SOCKET) {
//        fprintf(stderr, "Failed to create socket");
//        WSACleanup();
//        exit(EXIT_FAILURE);
//    }
//
//    // Set server address and port
//    struct sockaddr_in server_addr;
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_port = htons(8000); // Port for HTTP
//
//    // Convert URL to IP address
//    struct hostent *host = gethostbyname(url);
//    if (host == NULL) {
//        fprintf(stderr, "Failed to resolve hostname");
//        closesocket(sockfd);
//        WSACleanup();
//        exit(EXIT_FAILURE);
//    }
//    server_addr.sin_addr.s_addr = *((unsigned long *)host->h_addr);
//
//    // Connect to the server
//    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
//        fprintf(stderr, "Connection failed");
//        closesocket(sockfd);
//        WSACleanup();
//        exit(EXIT_FAILURE);
//    }
//
//    // Send HTTP GET request
//    const char *request_template = "GET /dk-find-out/image/upload/q_80,w_1920,f_auto/MA_00600259_vpf1m0.jpg HTTP/1.1\r\n"
//                                   "Host: localhost\r\n"
//                                   "Connection: close\r\n\r\n";
//    char * fileN = "image.jpg";
//    char request[1024];
//    snprintf(request, sizeof(request), request_template, url, url);
//    if (send(sockfd, request, strlen(request), 0) < 0) {
//        fprintf(stderr, "Send failed");
//        closesocket(sockfd);
//        WSACleanup();
//        exit(EXIT_FAILURE);
//    }
//
//    // Open the file to write the image data
//    FILE *image_file = fopen(fileN, "wb");
//    if (image_file == NULL) {
//        fprintf(stderr, "File open failed");
//        closesocket(sockfd);
//        WSACleanup();
//        exit(EXIT_FAILURE);
//    }
//
//    // Receive the response and write image data to the file
//    char buffer[1024];
//    int bytes_received;
//    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
//        fwrite(buffer, sizeof(char), bytes_received, image_file);
//    }
//
//    // Clean up and close the socket and file
//    fclose(image_file);
//    closesocket(sockfd);
//    WSACleanup();
//
//
//
//    // const char* url = "http://example.com/image.jpg";
//    // const char* filename = "image.jpg";
//    // FILE* fp = fopen(filename, "wb");
//    // if (fp == NULL) {
//    //     printf("Error opening file for writing.\n");
//    //     return 1;
//    // }
//
//    // FILE* stream = fopen(url, "rb");
//    // if (stream == NULL) {
//    //     printf("Error opening URL: %s\n", url);
//    //     fclose(fp);
//    //     return 1;
//    // }
//
//    // unsigned char buffer[4096];
//    // size_t bytesRead;
//    // while ((bytesRead = fread(buffer, 1, sizeof(buffer), stream)) > 0) {
//    //     fwrite(buffer, 1, bytesRead, fp);
//    // }
//
//    // fclose(stream);
//    // fclose(fp);
//
//    // printf("Image downloaded successfully.\n");
//
//}