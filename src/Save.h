#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <jpeglib.h>
#include "C:/msys64/mingw64/include/libpng16/png.h"

#define defautPath "data"

static int counter = 0;

#pragma pack(push, 1) // Ensure struct is packed tightly
typedef struct {
    unsigned short signature;     // File signature ("BM")
    unsigned int fileSize;        // Size of the BMP file
    unsigned int reserved;        // Reserved (should be 0)
    unsigned int dataOffset;      // Offset to the pixel data
    unsigned int headerSize;      // Size of the header
    int width;                    // Image width
    int height;                   // Image height (positive for bottom-up)
    unsigned short planes;        // Number of color planes (should be 1)
    unsigned short bitDepth;      // Number of bits per pixel
    unsigned int compression;     // Compression type (0 for uncompressed)
    unsigned int imageSize;       // Image size (0 for uncompressed)
    int xResolution;              // Horizontal resolution (pixels per meter, signed)
    int yResolution;              // Vertical resolution (pixels per meter, signed)
    unsigned int colorsUsed;      // Number of colors used
    unsigned int colorsImportant; // Number of important colors
} BMPHeader;
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

 void saveImageAsJPEG(char* filename, unsigned char* image, int width, int height, int channels, int quality) {
     setDestinationPath(filename);
     // Open the output JPEG file
     FILE* jpegFile = fopen(filename, "wb");
     if (!jpegFile) {
         printf("Error creating JPEG file: %s\n", filename);
         return;
     }

     // Initialize the JPEG compression structure
     struct jpeg_compress_struct cinfo;
     struct jpeg_error_mgr jerr;
     cinfo.err = jpeg_std_error(&jerr);
     jpeg_create_compress(&cinfo);
     jpeg_stdio_dest(&cinfo, jpegFile);

     // Set JPEG image attributes
     cinfo.image_width = width;
     cinfo.image_height = height;
     cinfo.input_components = 3; // Always 3 for RGB
     cinfo.in_color_space = JCS_RGB;

     // Set default compression parameters
     jpeg_set_defaults(&cinfo);
     jpeg_set_quality(&cinfo, quality, TRUE);

     // Start the JPEG compression
     jpeg_start_compress(&cinfo, TRUE);

     // Define row buffer to hold a single scanline
     JSAMPROW rowBuffer[1];
     int rowStride = width * 3; // 3 bytes per pixel (RGB)
     rowBuffer[0] = (JSAMPLE *)malloc(rowStride);

     // Write scanlines to the JPEG file
     while (cinfo.next_scanline < cinfo.image_height) {
         // Copy scanline data from the input image buffer
         unsigned char* inputRow = image + (cinfo.next_scanline * width * channels);
         for (int i = 0; i < width; ++i) {
             // Copy RGB values, skipping the alpha channel
             rowBuffer[0][i * 3 + 0] = inputRow[i * channels + 0]; // Red
             rowBuffer[0][i * 3 + 1] = inputRow[i * channels + 1]; // Green
             rowBuffer[0][i * 3 + 2] = inputRow[i * channels + 2]; // Blue
         }

         // Write the scanline to the JPEG file
         jpeg_write_scanlines(&cinfo, rowBuffer, 1);
     }

     // Finish the JPEG compression
     jpeg_finish_compress(&cinfo);
     jpeg_destroy_compress(&cinfo);

     // Close the output file
     fclose(jpegFile);

     // Free row buffer memory
     free(rowBuffer[0]);
     printf("Image suvsessfully Saved!"); // destination
 }


void saveImageAsPNG(const char* filename, unsigned char* image, int width, int height, int channels) {
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
    png_write_image(png_ptr,row_pointer);
    png_destroy_write_struct(&png_ptr, &info_ptr); // deallocate memory
    printf("Image suvsessfully Saved!");
}

void saveBitmap(const char* filename, unsigned char* image, int width, int height, int channels) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open the file for writing: %s\n", filename);
        return;
    }

    int bytesPerPixel = channels;
    int paddingSize = (4 - (width * bytesPerPixel) % 4) % 4; //(width * bytesperpixel) = bytes per row

    BMPHeader bmpHeader;
    bmpHeader.signature = 0x4D42;               // "BM"
    bmpHeader.fileSize = sizeof(BMPHeader) + (width * bytesPerPixel + paddingSize) * height;
    bmpHeader.reserved = 0;
    bmpHeader.dataOffset = sizeof(BMPHeader);
    bmpHeader.headerSize = 40;                   // Size of the BMP header
    bmpHeader.width = width;
    bmpHeader.height = height;
    bmpHeader.planes = 1;
    bmpHeader.bitDepth = bytesPerPixel * 8;
    bmpHeader.compression = 0;
    bmpHeader.imageSize = (width * bytesPerPixel + paddingSize) * height;
    bmpHeader.xResolution = 0;
    bmpHeader.yResolution = 0;
    bmpHeader.colorsUsed = 0;
    bmpHeader.colorsImportant = 0;

    fwrite(&bmpHeader, sizeof(BMPHeader), 1, file);

    unsigned char* rowBuffer = (unsigned char*)malloc(width * bytesPerPixel);
    if (!rowBuffer) {
        fclose(file);
        printf("Failed to allocate memory for row buffer\n");
        return;
    }

    for (int y = height - 1; y >= 0; --y) {
        int bufferIndex = 0;
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                rowBuffer[bufferIndex++] = image[(y * width + x) * channels + c];
            }
        }

        fwrite(rowBuffer, 1, width * bytesPerPixel + paddingSize, file);
    }
    free(rowBuffer);
    fclose(file);
    printf("Image successfully saved as BMP: %s\n", filename);
}


int saveStbi(unsigned  char* image , char* path , int width , int height , int channels){// use this
    int result = stbi_write_png(path, width, height, channels, image, width * channels);
    if (result == 0) {
        printf("Error saving the image.\n");
        return result;
    }
    printf("Image saved successfully.\n");
    return result;
}
