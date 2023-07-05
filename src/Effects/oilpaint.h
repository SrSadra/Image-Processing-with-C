#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to apply Oil Painting filter to an image
void applyOilPainting(unsigned char* image, int width, int height, int channels) {//you can get the level as brushsize
    int i, j, k;
    int radius = 5/ 2;//brush size=5

    // Create a temporary buffer to store the modified image
    unsigned char* tempImage = (unsigned char*)malloc(width * height * channels * sizeof(unsigned char));
    if (tempImage == NULL) {
        printf("Failed to allocate memory for temporary image buffer\n");
        return;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int index = (i * width + j) * channels;

            // Initialize color intensity counters for each channel
            int intensityCount[256] = {0};
            int maxCount = 0;
            int maxIntensity = 0;

            // Collect color intensities within the brush radius
            for (int y = -radius; y <= radius; y++) {
                for (int x = -radius; x <= radius; x++) {
                    int posX = j + x;
                    int posY = i + y;

                    // Skip pixels outside the image boundary
                    if (posX < 0 || posY < 0 || posX >= width || posY >= height)
                        continue;

                    int pixelIndex = (posY * width + posX) * channels;

                    // Calculate color intensity
                    int intensity = 0;
                    for (k = 0; k < channels; k++) {
                        intensity += image[pixelIndex + k];
                    }
                    intensity /= channels;

                    // Update intensity count for the corresponding intensity level
                    intensityCount[intensity]++;
                    if (intensityCount[intensity] > maxCount) {
                        maxCount = intensityCount[intensity];
                        maxIntensity = intensity;
                    }
                }
            }

            // Set the color of the current pixel to the color with the highest count
            for (k = 0; k < channels; k++) {
                tempImage[index + k] = maxIntensity;
            }
        }
    }

    // Copy the modified image back to the original image
    for (i = 0; i < width * height * channels; i++) {
        image[i] = tempImage[i];
    }

    // Free the temporary image buffer
    free(tempImage);
}
