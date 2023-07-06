#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void applyPencilSketch(unsigned char * image,int width,int height,int channels) {
    for (int i = 0; i < width * height; i++) {
        unsigned char red = image[i * channels];
        unsigned char green = image[i * channels + 1];
        unsigned char blue = image[i * channels + 2];
        unsigned char grayscale = (unsigned char)(0.2989 * red + 0.5870 * green + 0.1140 * blue);

        image[i * channels] = grayscale;
        image[i * channels + 1] = grayscale;
        image[i * channels + 2] = grayscale;
    }

    // Invert the grayscale image to create a negative effect
    for (int i = 0; i < width * height; i++) {
        unsigned char grayscale = imageData[i * channels];
        unsigned char inverted = 255 - grayscale;

        image[i * channels] = inverted;
        image[i * channels + 1] = inverted;
        image[i * channels + 2] = inverted;
    }

    // Apply Gaussian blur to smoothen the image
    // You can use a separate function to apply a Gaussian blur filter to the image

    // Blend the grayscale and blurred images to create a pencil sketch effect
    float strength = 0.6; // Strength of the pencil sketch effect (adjust as needed)
    for (int i = 0; i < width * height; i++) {
        unsigned char grayscale = image[i * channels];
        unsigned char blurred = image[i * channels]; // Use the blurred image data

        unsigned char pencilSketch = (unsigned char)(strength * grayscale + (1 - strength) * blurred);

        image[i * channels] = pencilSketch;
        image[i * channels + 1] = pencilSketch;
        image[i * channels + 2] = pencilSketch;
    }
}
