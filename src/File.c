//size_t write_callback(void* ptr, size_t size, size_t nmemb, FILE* stream);
//void readUrl(const char* url);
unsigned char* readfile(int* width , int* height  , int* channels , char* path , char* format);
unsigned char* download_image(const char* url, const char* filename , int* width , int* height , int* channels);
unsigned char* downloadImage(const char* url, int* width, int* height, int* channels);

