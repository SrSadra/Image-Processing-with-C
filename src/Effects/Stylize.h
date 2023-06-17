#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int windEffect(unsigned char* image, int width, int height , int channels, int direction , int strength) {
//    int channels = 4; // RGBA channels
    int amplitude = 10;
    int wavelength = 3;
    if (direction == 0) { // Left to right
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int srcX = x + (int)(amplitude * sinf(2 * M_PI * y / wavelength));

                if (srcX < 0) {
                    srcX = 0;
                } else if (srcX >= width) {
                    srcX = width - 1;
                }

                int srcIndex = (y * width + srcX) * channels;
                int destIndex = (y * width + x) * channels;

                for (int i = 0; i < channels; i++) {
                    image[destIndex + i] = image[srcIndex + i];
                }
            }
        }
    } else if (direction == 1) { // Right to left
        for (int y = 0; y < height; y++) {
            for (int x = width - 1; x >= 0; x--) {
                int srcX = x - (int)(amplitude * sinf(2 * M_PI * y / wavelength));

                if (srcX < 0) {
                    srcX = 0;
                } else if (srcX >= width) {
                    srcX = width - 1;
                }

                int srcIndex = (y * width + srcX) * channels;
                int destIndex = (y * width + x) * channels;

                for (int i = 0; i < channels; i++) {
                    image[destIndex + i] = image[srcIndex + i];
                }
            }
        }
    }
    return 0;
}