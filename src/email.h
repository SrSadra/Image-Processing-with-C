#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <curl/curl.h>
static char base64_decoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                       'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                       'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                       'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                       'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                       'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                       'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                       '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};
long firstAttachment(char *body, long emailSize, char *image_base64, char* file_name) {
    char *image_header = malloc((emailSize + 1) * sizeof(char));
    char *data = malloc((emailSize + 1) * sizeof(char));
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
    free(image_header);
    free(data);
}
//size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
//    return fwrite(ptr, size, nmemb, stream);
//}
unsigned char *base64_decode(const char *input, int input_length) {
    const int pl = 3 * input_length / 4;
    unsigned char *output = (unsigned char *)calloc(pl + 1, sizeof(unsigned char));
    int ol = 0;
    for (int i = 0; i < input_length; i += 4) {
        uint32_t block = 0;
        int block_length = 0;
        /* Convert 4 base64 characters to a 24-bit block */
        for (int j = 0; j < 4; j++) {
            block <<= 6;
            if (input[i + j] != '=') {
                const char *char_ptr = strchr(base64_decoding_table, input[i + j]);
                if (char_ptr != NULL) {
                    int index = char_ptr - base64_decoding_table;
                    block |= index;
                    block_length += 6;
                } else {
                    fprintf(stderr, "Invalid base64 character: %c\n", input[i + j]);
                    free(output);
                    return NULL;
                }
            } else {
                block_length -= 2;
            }
        }
        /* Convert the 24-bit block to 3 bytes */
        for (int j = 0; j < block_length / 8; j++) {
            output[ol++] = (block >> (16 - j * 8)) & 0xFF;
        }
    }
    output[ol] = '\0';
    return output;
}



int email(char* emailAddress , char* onePassword , char* destination) {
    CURL *curl;
    CURLcode res;
    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Set the POP3 server URL for Gmail
        curl_easy_setopt(curl, CURLOPT_URL, "pop3s://pop.gmail.com:995");
        // Set the login credentials
        curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress); //email
        curl_easy_setopt(curl, CURLOPT_PASSWORD, onePassword);//pass
        // Set the POP3 authentication method
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        // Specify the path to the trusted CA certificate file
        curl_easy_setopt(curl, CURLOPT_CAINFO, getenv("PEMFILE"));
        // Set SSL certificate verification options
        //if it was 1L and 2L it is secure
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
            FILE *emailFile = fopen("D:\\finalcproject\\src\\Data\\email.txt", "w");// file in system
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
            //finish fetching email
            char *emailBody = NULL;//full body of email
            long emailSize;//size of body
            size_t imageBase64Size;//?
            char *image_base64 = NULL;//decode of the
            unsigned char *image = NULL;
            char *file_name = NULL;
            // read email body from file
            FILE *emailFileRead = fopen("D:\\finalcproject\\src\\Data\\email.txt", "r");//read email file
            fseek(emailFileRead, 0, SEEK_END);//
            emailSize = ftell(emailFileRead);//size of email
            rewind(emailFileRead);//for the start of the file
            emailBody = malloc((emailSize + 1) * sizeof(char));
            fread(emailBody, sizeof(char), emailSize, emailFileRead);
            emailBody[emailSize] = '\0';
            fclose(emailFileRead);
            // finding image
            image_base64 = malloc((emailSize + 1) * sizeof(char));
            file_name = malloc((emailSize + 1) * sizeof(char));//?
            imageBase64Size = firstAttachment(emailBody, emailSize, image_base64, file_name);
            // decode base64 data
            image = base64_decode(image_base64, imageBase64Size - 1);


//            char *file_path=(char *) malloc(sizeof(char)*5000);
//            sprintf(file_path, "C:/Users/Tarahan IT/OneDrive/Desktop/picture/%s", file_name);


            printf("saving file to path %s\n", destination);
            FILE *imageFile = fopen(destination, "wb");
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

