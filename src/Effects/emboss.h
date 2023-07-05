#include <stdio.h>
#include <stdlib.h>

void applyEmbbossFilter(unsigned char* image, int width, int height, int channels) {
    int kernel[3][3] = {
            {-2, -1, 0},
            {-1, 1, 1},
            {0, 1, 2}
    };

    unsigned char* result = malloc(width * height * channels * sizeof(unsigned char));
    if (result == NULL) {
        printf("Failed to allocate memory\n");
        return;
    }

    int i, j, k;
    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            for (k = 0; k < channels; k++) {
                int sum = 0;

                // Convolve the kernel with the image pixels
                for (int m = -1; m <= 1; m++) {
                    for (int n = -1; n <= 1; n++) {
                        int pixelIndex = ((i + m) * width + (j + n)) * channels + k;
                        int kernelValue = kernel[m + 1][n + 1];
                        sum += image[pixelIndex] * kernelValue;
                    }
                }

                // Clamp the pixel value to the range [0, 255]
                result[(i * width + j) * channels + k] = (unsigned char)(sum > 255 ? 255 : (sum < 0 ? 0 : sum));
            }

            // Set alpha channel value to 255 (fully opaque) for RGBA images
            if (channels == 4) {
                result[(i * width + j) * channels + 3] = 255;
            }
        }
    }

    // Copy the result back to the original image
    for (i = 0; i < width * height * channels; i++) {
        image[i] = result[i];
    }
}
