#include <stdio.h>
void applyInvertFilter(unsigned char* image, int width, int height, int channels) {
    for (int i = 0; i < width * height; i++) {
        for (int j = 0; j < channels; j++) {
            // Calculate the index of the current pixel
            int index = i * channels + j;

            // Invert the pixel value
            image[index] = 255 - image[index];
        }
    }
}