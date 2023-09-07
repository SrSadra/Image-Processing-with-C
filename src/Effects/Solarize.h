#include <stdio.h>
#include <stdlib.h>

int applySolarizeFilter(unsigned char* image, int width, int height, int channels) {
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

    return 0;
}


int applyThresholding(unsigned char* image, int width, int height, int channels, unsigned char threshold) {
    int numPixels = width * height;
    for (int i = 0; i < numPixels; i++) {
        for (int c = 0; c < channels; c++) {
            int index = (i * channels) + c;
            if (image[index] < threshold) {
                image[index] = 0;  // Set pixel value to 0 (black)
            } else {
                image[index] = 255;  // Set pixel value to 255 (white)
            }

        }

    }
    return 0;
}