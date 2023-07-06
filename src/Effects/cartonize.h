#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void applyCartoonize(unsigned char* image,int width,int height,int channels) {
    // Apply Gaussian blur to reduce details
    // You can use a separate function to apply a Gaussian blur filter to the image

    // Convert the image to grayscale
    for (int i = 0; i < width * height; i++) {
        unsigned char red = image[i * channels];
        unsigned char green = image[i * channels + 1];
        unsigned char blue = image[i * channels + 2];
        unsigned char grayscale = (unsigned char)(0.2989 * red + 0.5870 * green + 0.1140 * blue);

        image[i * channels] = grayscale;
        image[i * channels + 1] = grayscale;
        image[i * channels + 2] = grayscale;
    }

    // Apply edge detection to enhance edges
    // You can use a separate function to apply an edge detection filter to the image

    // Threshold the image to create a binary result
    unsigned char threshold = 128;
    for (int i = 0; i < width * height; i++) {
        unsigned char grayscale = image[i * channels];
        unsigned char binary = grayscale < threshold ? 0 : 255;

        image[i * channels] = binary;
        image[i * channels + 1] = binary;
        image[i * channels + 2] = binary;
    }
}
