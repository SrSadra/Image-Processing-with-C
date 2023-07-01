#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RADIUS 5
#define INTENSITY_LEVELS 256


void applyOilPaintingFilter(unsigned char* image,int width , int height ,int channels); {
    int x, y, i, j;
    int intensityCount[INTENSITY_LEVELS] = {0};
    unsigned char* blurredImage = malloc(height * width * channels * sizeof(unsigned char));

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (i = 0; i < INTENSITY_LEVELS; i++) {
                intensityCount[i] = 0;
            }

            // Calculate the intensity levels of nearby pixels within the radius
            for (i = -RADIUS; i <= RADIUS; i++) {
                for (j = -RADIUS; j <= RADIUS; j++) {
                    int nx = x + i;
                    int ny = y + j;

                    // Ensure the pixel coordinates are within the image bounds
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        unsigned char intensity = 0;

                        // Calculate intensity based on the number of channels
                        if (channels == 3) {
                            intensity = (image[(ny * width + nx) * 3] + image[(ny * width + nx) * 3 + 1] + image[(ny * width + nx) * 3 + 2]) / 3;
                        } else if (channels == 4) {
                            intensity = (image[(ny * width + nx) * 4] + image[(ny * width + nx) * 4 + 1] + image[(ny * width + nx) * 4 + 2]) / 3;
                        }

                        intensityCount[intensity]++;
                    }
                }
            }

            int maxCount = 0;
            int maxIntensity = 0;

            // Find the intensity level with the maximum count
            for (i = 0; i < INTENSITY_LEVELS; i++) {
                if (intensityCount[i] > maxCount) {
                    maxCount = intensityCount[i];
                    maxIntensity = i;
                }
            }

            // Set the pixel value to the color with the most occurrences in the neighborhood
            for (i = 0; i < channels; i++) {
                blurredImage[(y * width + x) * channels + i] = maxIntensity;
            }
        }
    }

    // Copy the blurred image back to the original image
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            for (i = 0; i < channels; i++) {
                image[(y * width + x) * channels + i] = blurredImage[(y * width + x) * channels + i];
            }
        }
    }
}