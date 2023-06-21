//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//
//#define BUFFER_SIZE 1024
//
//// Function to download an image from a URL using sockets
//void download_image(const char *url, unsigned char **image_data, size_t *image_size) {
//    WSADATA wsaData;
//    SOCKET sockfd;
//    struct sockaddr_in server_addr;
//    char request[BUFFER_SIZE];
//    char response_header[BUFFER_SIZE];
//    unsigned char buffer[BUFFER_SIZE];
//    ssize_t received_bytes, total_bytes = 0;
//    int header_end = 0;
//
//    // Initialize Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        printf("Failed to initialize Winsock\n");
//        return;
//    }
//
//    // Create socket
//    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//        printf( "Error creating socket: %ld\n", WSAGetLastError());
//        WSACleanup();
//        return;
//    }
//
//    // Set server address and port
//    memset(&server_addr, 0, sizeof(server_addr));
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_port = htons(80);
//
//    // Convert URL to IP address
//    if (inet_pton(AF_INET, url, &(server_addr.sin_addr)) <= 0) {
//        printf("Invalid address or address not supported\n");
//        closesocket(sockfd);
//        WSACleanup();
//        return;
//    }
//
//    // Connect to the server
//    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
//        printf("Connection failed: %ld\n", WSAGetLastError());
//        closesocket(sockfd);
//        WSACleanup();
//        return;
//    }
//
//    // Send HTTP GET request
//    snprintf(request, BUFFER_SIZE, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", url);
//    if (send(sockfd, request, strlen(request), 0) == SOCKET_ERROR) {
//        printf("Failed to send request: %ld\n", WSAGetLastError());
//        closesocket(sockfd);
//        WSACleanup();
//        return;
//    }
//
//    // Receive response
//    while ((received_bytes = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
//        // Check if the end of the response header is reached
//        if (!header_end) {
//            memcpy(response_header + total_bytes, buffer, received_bytes);
//            total_bytes += received_bytes;
//
//            // Check if the response header is complete
//            char *header_end_ptr = strstr(response_header, "\r\n\r\n");
//            if (header_end_ptr != NULL) {
//                header_end = 1;
//
//                // Calculate the size of the image data
//                *image_size = total_bytes - (header_end_ptr - response_header) - 4;
//
//                // Allocate memory for the image data
//                *image_data = (unsigned char *)malloc(*image_size);
//                if (*image_data == NULL) {
//                    printf("Error allocating memory for image\n");
//                    closesocket(sockfd);
//                    WSACleanup();
//                    return;
//                }
//
//                // Copy the image data from the response buffer
//                memcpy(*image_data, header_end_ptr + 4, *image_size);
//            }
//        } else {
//            // Copy the remaining image data
//            memcpy(*image_data + total_bytes - *image_size, buffer, received_bytes);
//            total_bytes += received_bytes;
//        }
//    }
//
//    // Cleanup
//    closesocket(sockfd);
//    WSACleanup();
//}
//int main() {
//    const char *image_url = "https://photos5.appleinsider.com/gallery/42715-82913-41553-80620-10793A9C-C3A1-49D4-B416-2EEB7E6EFE51-xl-xl.jpg";
//    unsigned char *image_data;
//    size_t image_size;
//
//    // Call the download_image function
//    download_image(image_url, &image_data, &image_size);
//
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 1024

// Function to download an image from a URL using sockets
void download_image(const char *host,const char *url, unsigned char **image_data, size_t *image_size) {
    WSADATA wsaData;
    SOCKET sockfd;
    struct addrinfo hints, *result = NULL;
    char request[BUFFER_SIZE];
    char response_header[BUFFER_SIZE];
    unsigned char buffer[BUFFER_SIZE];
    ssize_t received_bytes, total_bytes = 0;
    int header_end = 0;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock\n");
        return;
    }

    // Set up the hints structure for address resolution
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the URL to IP address
    if (getaddrinfo(host, url, &hints, &result) != 0) {
        printf("Failed to resolve address for %s\n", url);
        WSACleanup();
        return;
    }

    // Create socket
    sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sockfd == INVALID_SOCKET) {
        printf("Error creating socket: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Connect to the server
    if (connect(sockfd, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("Connection failed: %ld\n", WSAGetLastError());
        closesocket(sockfd);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Send HTTP GET request
    snprintf(request, BUFFER_SIZE, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", url);
    if (send(sockfd, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Failed to send request: %ld\n", WSAGetLastError());
        closesocket(sockfd);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Receive response
   while ((received_bytes = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) { //had problem
        // Check if the end of the response header is reached
        if (!header_end) {
            memcpy(response_header + total_bytes, buffer, received_bytes);
            total_bytes += received_bytes;

            // Check if the response header is complete
            char *header_end_ptr = strstr(response_header, "\r\n\r\n");
            if (header_end_ptr != NULL) {
                header_end = 1;

                // Calculate the size of the image data
                *image_size = total_bytes - (header_end_ptr - response_header) - 4;

                // Allocate memory for the image data
                *image_data = (unsigned char *)malloc(*image_size);
                if (*image_data == NULL) {
                    printf("Error allocating memory for image\n");
                    closesocket(sockfd);
                    freeaddrinfo(result);
                    WSACleanup();
                    return;
                }

                // Copy the image data from the response buffer
                memcpy(*image_data, header_end_ptr + 4, *image_size);
            }
        } else {
            // Copy the remaining image data
            memcpy(*image_data + total_bytes - *image_size, buffer, received_bytes);
            total_bytes += received_bytes;
        }
    }

    // Cleanup
    closesocket(sockfd);
    freeaddrinfo(result);
    WSACleanup();
}

int main() {
    const char *image_url = "https://th.bing.com/th/id/R.adfe3ea4e2243d6943ed929eeec82576?rik=lGsaekEMeREGqA&pid=ImgRaw";
    char host_name[BUFFER_SIZE];

// Find the start of the host name
    const char *start = strstr(image_url, "://");
    if (start == NULL) {
        printf("Invalid URL format\n");
        return 1;
    }
    start += 3;  // Move past "://"

// Find the end of the host name
    const char *end = strchr(start, '/');
    if (end == NULL) {
        printf("Invalid URL format\n");
        return 1;
    }

// Copy the host name into a separate string
    size_t length = end - start;
    if (length >= BUFFER_SIZE) {
        printf("Host name is too long\n");
        return 1;
    }
    memcpy(host_name, start, length);
    host_name[length] = '\0';
    unsigned char *image_data;
    size_t image_size;

// Pass the extracted host name to the download_image function
    download_image(host_name,image_url, &image_data, &image_size);

    return 0;
}
