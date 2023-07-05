#include <stdio.h>
#include <stdlib.h>

// Function to apply Posterize filter to an image
void applyPosterize(unsigned char* image, int width, int height, int channels) {//you can get the level as input
    int i, j, k;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int index = (i * width + j) * channels;

            // Apply posterize effect to each channel
            for (k = 0; k < channels; k++) {
                unsigned char pixel = image[index + k];
                unsigned char newPixel = ((pixel * 4) / 255) * (255 / 4);//level=4
                image[index + k] = newPixel;
            }
        }
    }
}
