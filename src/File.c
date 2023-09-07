//size_t write_callback(void* ptr, size_t size, size_t nmemb, FILE* stream);
//void readUrl(const char* url);
unsigned char* readfile(int* width , int* height  , int* channels , char* path , char* format);
int downloadImage(const char* url, const char* file);
unsigned char* readBMPImage(const char* filename , int* width , int* height , int* channels);
