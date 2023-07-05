#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <curl/curl.h>
#include <openssl/evp.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

long extract_first_image(char *body, long emailSize, char *image_base64, char* file_name);
size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream);
unsigned char *base64_decode(const char *input, int input_length);

int email() {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Set the POP3 server URL for Gmail
        curl_easy_setopt(curl, CURLOPT_URL, "pop3s://pop.gmail.com:995");

        // Set the login credentials
        curl_easy_setopt(curl, CURLOPT_USERNAME, "zshiva179@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "vtthwquqdijjnpby");

        // Set the POP3 authentication method
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        // Specify the path to the trusted CA certificate file
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Users\\Novin\\CLionProjects\\untitled147\\cacert-2023-05-30.pem");
        // Set SSL certificate verification options
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Perform the login request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Login failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Login successful!\n");

            // Set the command to retrieve the first email
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "RETR 1");

            // Set the callback function to write the email data to a file
            FILE *emailFile = fopen("C:/Users/Tarahan IT/OneDrive/Desktop/picture/email.txt", "w");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, emailFile);

            // Perform the request to download the email
            res = curl_easy_perform(curl);
            fclose(emailFile);

            if (res != CURLE_OK) {
                fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
                return 1;
            }

            printf("Email downloaded successfully!\n");

            char *emailBody = NULL;
            long emailSize;
            size_t imageBase64Size;
            char *image_base64 = NULL;
            unsigned char *image = NULL;
            char *file_name = NULL;

            // read email body from file
            FILE *emailFileRead = fopen("C:/Users/Tarahan IT/OneDrive/Desktop/picture/email.txt", "r");
            fseek(emailFileRead, 0, SEEK_END);
            emailSize = ftell(emailFileRead);
            rewind(emailFileRead);
            emailBody = malloc((emailSize + 1) * sizeof(char));
            fread(emailBody, sizeof(char), emailSize, emailFileRead);
            emailBody[emailSize] = '\0';
            fclose(emailFileRead);

            // finding image
            image_base64 = malloc((emailSize + 1) * sizeof(char));
            file_name = malloc((1000 + 1) * sizeof(char));

            imageBase64Size = extract_first_image(emailBody, emailSize, image_base64, file_name);

            // decode base64 data
            image = base64_decode(image_base64, imageBase64Size - 1);

            // Find the attachment image data
            char file_path[2000];
            sprintf(file_path, "C:/Users/Tarahan IT/OneDrive/Desktop/picture/%s", file_name);
            printf("saving file to path %s\n", file_path);
            FILE *imageFile = fopen(file_path, "wb");
            fwrite(image, sizeof(char), 3 * imageBase64Size / 4, imageFile);

            fclose(imageFile);

            // Clean up
            free(emailBody);
            free(image_base64);
            curl_easy_cleanup(curl);

            return 0;
        }
    } else {
        fprintf(stderr, "Failed to initialize libcurl.\n");
    }
    return 1;
}

long extract_first_image(char *body, long emailSize, char *image_base64, char* file_name) {
    char *image_header = malloc((emailSize + 1) * sizeof(char));
    char *data = malloc((emailSize + 1) * sizeof(char));
    // TODO: fix the memory leak


    long j = 0; // base64 image index
    long k = 0; // file name index

    image_header = strstr(body, "Content-Type: image/");

    if(image_header) {

        // extract file name
        long i = 0;
        while(image_header[i++] != '"');
        while(image_header[i] != '"') {
            file_name[k++] = image_header[i++];
        }
        file_name[k] = '\0';

        printf("First image file name: %s\n", file_name);

        // extract base64 image
        printf("extracting base64 image...\n");
        data = 4 + strstr(image_header, "\r\n\r\n");

        for (i = 0; data[i] != '\0'; ++i) {
            if(data[i] == '\r' || data[i] == '\n') {
                continue;
            }

            if(data[i] == '-') {
                image_base64[j++] = '\0';
                break;
            }
            image_base64[j++] = data[i];
        }
        return j;
    } else {
        printf("attachment not found");
        exit(1);
    }
}

unsigned char *base64_decode(const char *input, int input_length) {
    printf("decoding base64...\n");
    const int pl = 3 * input_length / 4;
    unsigned char *output = calloc(pl+1, 1);
    const int ol = EVP_DecodeBlock(output, input, input_length);
    if (pl != ol) { fprintf(stderr, "Whoops, decode predicted %d but we got %d\n", pl, ol); }
    return output;
}


size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}