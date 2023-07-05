#include <stdio.h>
#include <stdlib.h>
// Struct to hold BMP image data
typedef struct {
    unsigned char* data;  // Pointer to image data
    int width;            // Image width
    int height;           // Image height
    int channels;         // Number of color channels
    int imageSize;        // Image size in bytes
} BMPImage;

BMPImage* readBMPImage(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    // Seek to the start of image data offset
    fseek(file, 10, SEEK_SET);
    unsigned char imageDataOffset[4];
    fread(imageDataOffset, sizeof(unsigned char), 4, file);
    int dataOffset = *(int*)imageDataOffset;

    // Seek to the image width offset
    fseek(file, 18, SEEK_SET);
    unsigned char imageWidth[4];
    fread(imageWidth, sizeof(unsigned char), 4, file);
    int width = *(int*)imageWidth;

    // Seek to the image height offset
    fseek(file, 22, SEEK_SET);
    unsigned char imageHeight[4];
    fread(imageHeight, sizeof(unsigned char), 4, file);
    int height = *(int*)imageHeight;

    // Seek to the image color depth offset
    fseek(file, 28, SEEK_SET);
    unsigned char imageColorDepth[2];
    fread(imageColorDepth, sizeof(unsigned char), 2, file);
    int colorDepth = *(short*)imageColorDepth;

    // Calculate the number of color channels
    int channels = colorDepth / 8;

    // Calculate the image size
    fseek(file, 34, SEEK_SET);
    unsigned char imageSizeBytes[4];
    fread(imageSizeBytes, sizeof(unsigned char), 4, file);
    int imageSize = *(int*)imageSizeBytes;

    // Allocate memory for image data
    unsigned char* imageData = (unsigned char*)malloc(imageSize);
    if (imageData == NULL) {
        printf("Failed to allocate memory for image data\n");
        fclose(file);
        return NULL;
    }

    // Read image data
    fseek(file, dataOffset, SEEK_SET);
    fread(imageData, sizeof(unsigned char), imageSize, file);

    // Close the file
    fclose(file);

    // Create the BMPImage struct and populate it with the image data
    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    if (image == NULL) {
        printf("Failed to allocate memory for BMPImage struct\n");
        free(imageData);
        return NULL;
    }

    image->data = imageData;
    image->width = width;
    image->height = height;
    image->channels = channels;
    image->imageSize = imageSize;

    return image;
}
void saveBMPImage(const char* filename, BMPImage* image) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to create file: %s\n", filename);
        return;
    }

    // Write BMP header
    unsigned char header[54] = {
            0x42, 0x4D,             // Signature: BM
            0, 0, 0, 0,             // File size
            0, 0,                   // Reserved
            0, 0,                   // Reserved
            54, 0, 0, 0,            // Data offset
            40, 0, 0, 0,            // Header size
            0, 0, 0, 0,             // Image width
            0, 0, 0, 0,             // Image height
            1, 0,                   // Planes
            24, 0,                  // Bits per pixel
            0, 0, 0, 0,             // Compression
            0, 0, 0, 0,             // Image size
            0, 0, 0, 0,             // X resolution
            0, 0, 0, 0,             // Y resolution
            0, 0, 0, 0,             // Colors used
            0, 0, 0, 0              // Colors important
    };

    // Update header with image data
    *(int*)&header[2] = 54 + image->imageSize;        // File size
    *(int*)&header[18] = image->width;                // Image width
    *(int*)&header[22] = image->height;               // Image height
    *(int*)&header[34] = image->imageSize;            // Image size

    // Write header to file
    fwrite(header, sizeof(unsigned char), 54, file);

    // Write image data to file
    fwrite(image->data, sizeof(unsigned char), image->imageSize, file);

    // Close the file
    fclose(file);
}
void freeBMPImage(BMPImage* image) {
    if (image != NULL) {
        free(image->data);
        free(image);
    }
}

//int main() {
//    const char* filename = "C:\\Users\\Tarahan IT\\Downloads\\54.bmp";
//
//    BMPImage* image = readBMPImage(filename);
//    if (image == NULL) {
//        printf("Failed to read BMP image\n");
//        return 1;
//    }
//    const char* newFilename = "C:\\Users\\Tarahan IT\\Downloads\\549.bmp";
//    saveBMPImage(newFilename, image);
//    printf("Image saved to: %s\n", newFilename);
//    return 0;
//}