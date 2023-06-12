#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #define cimg_use_jpeg
// #ifdef cimg_use_jpeg
// #define HAVE_BOOLEAN
// #define JPEG_INTERNALS
// #include <jpeglib.h>
// #include "D:\\new project c\\src\\lib\\jpeg-9e-h2bbff1b_1\\Library\include\\jpeglib.h"
// extern "C" {
// #include "D:\\c-effect-project\\stb_image\\jpeg\\jpeglib.h"
// #include "setjmp.h"
// }
// #endif


#include "C:/msys64/mingw64/include/libpng16/png.h"

#define defautPath "data"

static int counter = 0;

#pragma pack(push, 1) // Ensure struct is packed tightly
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
#pragma pack(pop)


void setDestinationPath(char* filePath){
    if (*filePath == '0'){   
        char arr1[1000];
        char arr2[1000] = "//";
        sprintf(arr1 , "%d", counter);
        strcat(arr2 , arr1);
        filePath = defautPath;
        strcat(filePath , arr2);
    }
    return;
}

// void saveImageAsJPEG(char* filename, unsigned char* image, int width, int height, int channels, int quality) {
//     setDestinationPath(filename);
//     // Open the output JPEG file
//     FILE* jpegFile = fopen(filename, "wb");
//     if (!jpegFile) {
//         printf("Error creating JPEG file: %s\n", filename);
//         return;
//     }

//     // Initialize the JPEG compression structure
//     struct jpeg_compress_struct cinfo;
//     struct jpeg_error_mgr jerr;
//     cinfo.err = jpeg_std_error(&jerr);
//     jpeg_create_compress(&cinfo);
//     jpeg_stdio_dest(&cinfo, jpegFile);

//     // Set JPEG image attributes
//     cinfo.image_width = width;
//     cinfo.image_height = height;
//     cinfo.input_components = channels;
//     cinfo.in_color_space = JCS_RGB;

//     // Set default compression parameters
//     jpeg_set_defaults(&cinfo);
//     jpeg_set_quality(&cinfo, quality, TRUE);

//     // Start the JPEG compression
//     jpeg_start_compress(&cinfo, TRUE);

//     // Define row buffer to hold a single scanline
//     JSAMPROW rowBuffer[1];
//     int rowStride = width * channels;
//     rowBuffer[0] = (JSAMPLE *)malloc(rowStride);

//     // Write scanlines to the JPEG file
//     while (cinfo.next_scanline < cinfo.image_height) {
//         // Copy scanline data from the input image buffer
//         unsigned char* inputRow = image + (cinfo.next_scanline * rowStride);
//         memcpy(rowBuffer[0], inputRow, rowStride);

//         // Write the scanline to the JPEG file
//         jpeg_write_scanlines(&cinfo, rowBuffer, 1);
//     }

//     // Finish the JPEG compression
//     jpeg_finish_compress(&cinfo);
//     jpeg_destroy_compress(&cinfo);

//     // // Close the output file
//     // fclose(jpegFile);

//     // Free row buffer memory
//     free(rowBuffer[0]);
//     printf("Image suvsessfully Saved!"); // destination
// }


void saveImageAsPNG(const char* filename, unsigned char* image, int width, int height, int channels) {
    printf("alola");
    setDestinationPath(filename);
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        printf("Error creating PNG write structure\n");
        fclose(file);
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        printf("Error creating PNG info structure\n");
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(file);
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("Error during PNG writing\n");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        return;
    }

    png_init_io(png_ptr, file);

    int color_type;
    switch (channels) {
        case 1:
            color_type = PNG_COLOR_TYPE_GRAY;
            break;
        case 2:
            color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
            break;
        case 3:
            color_type = PNG_COLOR_TYPE_RGB;
            break;
        case 4:
            color_type = PNG_COLOR_TYPE_RGB_ALPHA;
            break;
        default:
            printf("Invalid number of channels\n");
            png_destroy_write_struct(&png_ptr, &info_ptr);
            fclose(file);
            return;
    }

    png_set_IHDR(png_ptr, info_ptr, width, height, 8, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    png_bytep row_pointer[height];
    for (int y = 0; y < height; ++y)
        row_pointer[y] = &image[y * width * channels];

    png_write_image(png_ptr, row_pointer);
    png_destroy_write_struct(&png_ptr, &info_ptr); // deallocate memory
    printf("Image suvsessfully Saved!");
}

void saveBitmap(const char* filename, unsigned char* image, int width, int height) {
    setDestinationPath(filename);
    printf("%s", filename);
    // Calculate the size of the image data and the BMP file
    unsigned int imageSize = width * height * 3; // Assuming 24 bits per pixel (RGB)
    unsigned int fileSize = sizeof(BitmapHeader) + imageSize;

    // Create and populate the bitmap header
    BitmapHeader header;
    header.signature = 0x4D42; // 'BM' for bitmap
    header.fileSize = fileSize;
    header.reserved = 0;
    header.dataOffset = sizeof(BitmapHeader);
    header.headerSize = sizeof(BitmapHeader) - 14; // Size of the header excluding the common fields
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bitsPerPixel = 24; // 24 bits per pixel (RGB)
    header.compression = 0; // No compression
    header.imageSize = imageSize;
    header.horizontalRes = 0; // Use default resolution (72 pixels per meter)
    header.verticalRes = 0; // Use default resolution (72 pixels per meter)
    header.colors = 0; // No color palette
    header.importantColors = 0; // All colors are important

    // Create a file and write the bitmap header followed by the pixel data
    FILE* file = fopen(filename, "wb");
    if (file) {
        fwrite(&header, sizeof(BitmapHeader), 1, file);
        fwrite(image, 1, imageSize, file);
        fclose(file);
        printf("Bitmap saved successfully.\n");
    } else {
        printf("Error opening the file for writing.\n");
    }
}

// int main() {
//     // Example usage
//     int width = 320;
//     int height = 240;
//     unsigned char* image = (unsigned char*)malloc(width * height * 3); // RGB image with 8 bits per channel

//     // Populate the image data...

//     saveImageAsPNG("output.png", image, width, height);

//     free(image);

//     return 0;
// }

