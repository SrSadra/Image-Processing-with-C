#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int applyCartoonize(unsigned char* image,int width,int height,int channels) {

    for (int i = 0; i < width * height; i++) {
        unsigned char red = image[i * channels];
        unsigned char green = image[i * channels + 1];
        unsigned char blue = image[i * channels + 2];

        unsigned char grayscale = (unsigned char)(0.2989 * red + 0.5870 * green + 0.1140 * blue);

        for (int c = 0; c < channels; c++) {
            if (c != 3) {
                image[i * channels + c] = grayscale;
            }
        }
    }

    unsigned char threshold = 128;
    for (int i = 0; i < width * height; i++) {
        for (int c = 0; c < channels; c++) {
            if (c != 3) {
                unsigned char value = image[i * channels + c];
                unsigned char binary = value < threshold ? 0 : 255;
                image[i * channels + c] = binary;
            }
        }
    }

    return 0;
}



int applyInvertFilter(unsigned char* image, int width, int height, int channels) {
    for (int i = 0; i < width * height; i++) {
        for (int c = 0; c < channels; c++) {
            if (c != 3){
                image[i * channels + c] = 255 - image[i * channels + c];
            }
        }
    }
    return 0;
}




int applyPencilSketch(unsigned char * image,int width,int height,int channels) {
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
        unsigned char grayscale = image[i * channels];
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
    return 0;
}



int applyPosterize(unsigned char* image, int width, int height, int channels) {
    int i, j, k;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int index = (i * width + j) * channels;

            for (k = 0; k < channels; k++) {
                unsigned char pixel = image[index + k];
                unsigned char newPixel = ((pixel * 4) / 255) * (255 / 4);//level=4
                image[index + k] = newPixel;
            }
        }
    }

    return 0;
}