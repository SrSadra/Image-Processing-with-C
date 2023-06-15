#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

void rotateImage(int * image, float degrees) {
    int width, height, channels;

    // Convert degrees to radians
    float radians = degrees * 3.14159f / 180.0f;

    // Calculate new width and height for rotated image
    int newWidth = abs(width * cos(radians)) + abs(height * sin(radians));
    int newHeight = abs(width * sin(radians)) + abs(height * cos(radians));

    unsigned char* rotatedImage = (unsigned char*)malloc(newWidth * newHeight * channels);
    stbir_resize_uint8(image, width, height, 0, rotatedImage, newWidth, newHeight, 0, channels);

    // Rotate the image
    stbir_rotate_uint8(rotatedImage, newWidth, newHeight, 0, rotatedImage, degrees, width / 2, height / 2, channels);

    // Generate the output file name based on the input file name and rotation angle
    char outputPath[256];
    snprintf(outputPath, sizeof(outputPath), "rotated_%.1f_%s", degrees, inputPath);

    stbi_write_jpg(outputPath, newWidth, newHeight, channels, rotatedImage, 100);

    stbi_image_free(image);
    free(rotatedImage);

    printf("Image rotated successfully. Output: %s\n", outputPath);
}

//int main() {
//    const char* inputPath = "input.jpg";
//    float degrees = 45.0f;
//
//    rotateImage(inputPath, degrees);
//
//    return 0;
//}

