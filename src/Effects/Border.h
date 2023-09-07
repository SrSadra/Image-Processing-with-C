#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VIGNETTE_STRENGTH 0.5

int apply_vignette(unsigned char* image,int width , int height ,int channels) {
    int center_x = width / 2;
    int center_y = height / 2;
    double max_distance = sqrt(center_x * center_x + center_y * center_y);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;

            double distance = sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
            double intensity = 1.0 - (distance / max_distance) * VIGNETTE_STRENGTH;

            image[index] = (unsigned char)(image[index] * intensity); // Red channel
            image[index + 1] = (unsigned char)(image[index + 1] * intensity); // Green channel
            image[index + 2] = (unsigned char)(image[index + 2] * intensity); // Blue channel
            // Leave the alpha channel unchanged (image[index + 3])
        }
    }

    return 0;
}
