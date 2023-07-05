#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <winsock2.h>
// #include <windows.h>
// #include <sys/types.h>

// #include "stb_image/inet.h"
// #include <unistd.h>
// #include <netinet/in.h>
// #include "stb_image/in.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define bufferSize 1000


// #pragma comment(lib, "ws2_32.lib")

// void initialize(int type){
    
// }

size_t write_callback(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

unsigned char* readfile(int* width , int* height  , int* channels , char* path){
    unsigned char* image = stbi_load(path, width, height, channels, STBI_rgb);
    if (image == NULL){
        printf("Error reading the image");
        return NULL;
    }
    return image;
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
