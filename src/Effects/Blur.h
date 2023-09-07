#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int applyGaussianBlurFilter(unsigned char* image, int width, int height, int channels) {
    // Gaussian kernel
    float kernel[5][5] = {
            {0.003765, 0.015019, 0.023792, 0.015019, 0.003765},
            {0.015019, 0.059912, 0.094907, 0.059912, 0.015019},
            {0.023792, 0.094907, 0.150342, 0.094907, 0.023792},
            {0.015019, 0.059912, 0.094907, 0.059912, 0.015019},
            {0.003765, 0.015019, 0.023792, 0.015019, 0.003765}
    };
    unsigned char* blurredImage = malloc(width * height * channels * sizeof(unsigned char));

    int x, y, i, j, k, l;

    // Apply the Gaussian blur kernel to each pixel
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (k = 0; k < channels; k++) {
                float sum = 0.0;
                int pixelIndex = (y * width + x) * channels + k;

                // Apply the kernel to the pixel and its neighboring pixels
                for (i = -5 / 2; i <= 5 / 2; i++) {
                    for (j = -5 / 2; j <= 5 / 2; j++) {
                        int nx = x + j;
                        int ny = y + i;

                        // Ensure the pixel coordinates are within the image bounds
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            int kernelIndex = (i + 5 / 2) * 5 + (j + 5 / 2);
                            int neighborPixelIndex = (ny * width + nx) * channels + k;
                            float kernelValue = kernel[i + 5 / 2][j + 5 / 2];

                            sum += image[neighborPixelIndex] * kernelValue;
                        }
                    }
                }

                blurredImage[pixelIndex] = (unsigned char)round(sum);
            }
        }
    }
    // Copy the blurred image back to the original image
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (k = 0; k < channels; k++) {
                int pixelIndex = (y * width + x) * channels + k;
                image[pixelIndex] = blurredImage[pixelIndex];
            }
        }
    }
    return 0;
}
