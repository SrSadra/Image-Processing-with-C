int makecolor(unsigned char * image ,unsigned char color , int i , int width , int height , int channels);
int makeGray(unsigned char * image, int width , int height , int channels);
void brightness(unsigned char * image , int width , int height , int channels , float percent );
void rgbToHsl(unsigned char r, unsigned char g, unsigned char b, float* h, float* s, float* l);
void hslToRgb(float h, float s, float l, unsigned char* r, unsigned char* g, unsigned char* b);
int applyHslAdjustment(unsigned char* image, int width, int height,int channels ,float hue, float saturation, float lightness);
int applySepiaFilter(unsigned char* image, int width, int height, int channels);//shvi

