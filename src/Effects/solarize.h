#include <stdio.h>
#include <stdlib.h>

void applySolarizeFilter(unsigned char* image, int width, int height, int channels) {
    int maxIntensity = 255;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width * channels; j += channels) {
            for (int k = 0; k < channels; k++) {
                // Calculate the complement of the pixel intensity
                int intensity = image[i * width * channels + j + k];
                int complement = maxIntensity - intensity;

                // Set the pixel value to the complement if it is greater than the original intensity
                if (complement > intensity) {
                    image[i * width * channels + j + k] = complement;
                }
            }

            // Set alpha channel value to 255 (fully opaque) for RGBA images
            if (channels == 4) {
                image[i * width * channels + j + 3] = 255;
            }
        }
    }
}