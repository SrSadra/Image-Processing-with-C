long firstAttachment(char *body, long emailSize, char *image_base64, char* file_name);
size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream);
unsigned char *base64_decode(const char *input, int input_length) ;
int email(char* emailAddress , char* onePassword , char* destination);