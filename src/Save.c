typedef struct {
    unsigned short signature;    // File type signature ('BM' for bitmap)
    unsigned int fileSize;       // Size of the BMP file
    unsigned int reserved;       // Reserved, set to 0
    unsigned int dataOffset;     // Offset to the pixel data
    unsigned int headerSize;     // Size of the DIB header
    int width;                   // Width of the image
    int height;                  // Height of the image
    unsigned short planes;       // Number of color planes, set to 1
    unsigned short bitsPerPixel; // Bits per pixel (usually 24 for RGB)
    unsigned int compression;    // Compression method (usually 0 for uncompressed)
    unsigned int imageSize;      // Size of the raw pixel data
    int horizontalRes;           // Horizontal resolution (pixels per meter)
    int verticalRes;             // Vertical resolution (pixels per meter)
    unsigned int colors;         // Number of colors in the palette, set to 0 for RGB
    unsigned int importantColors; // Number of important colors, set to 0
} BitmapHeader;

void saveBitmap(const char* filename, unsigned char* image, int width, int height);
void setDestinationPath(char* filePath);
void saveImageAsJPEG(char* filename, unsigned char* image, int width, int height, int channels, int quality);
void saveImageAsPNG(char* filename, unsigned char* image, int width, int height, int channels);
int saveStbi(unsigned  char* image , char* path , int width , int height , int channels);
