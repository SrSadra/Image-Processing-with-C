#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void applyHalftone(unsigned char* image,int width,int height,int channels ) {
    unsigned char* imageData = image->data;
    // Define halftone pattern matrix
    int patternSize = 4;
    int patternMatrix[4][4] = {
            { 15,  7, 13,  5 },
            {  3, 11,  1,  9 },
            { 12,  4, 14,  6 },
            {  0,  8,  2, 10 }
    };
    for (int y = 0; y < height; y += patternSize) {
        for (int x = 0; x < width; x += patternSize) {
            // Apply halftone to a 4x4 pixel block
            for (int row = 0; row < patternSize; row++) {
                for (int col = 0; col < patternSize; col++) {
                    if (y + row < height && x + col < width) {
                        int pixelIndex = ((y + row) * width + (x + col)) * channels;

                        // Calculate grayscale value from RGB channels
                        unsigned char red = imageData[pixelIndex];
                        unsigned char green = imageData[pixelIndex + 1];
                        unsigned char blue = imageData[pixelIndex + 2];
                        unsigned char grayscale = (unsigned char)(0.2989 * red + 0.5870 * green + 0.1140 * blue);

                        // Compare grayscale value with halftone pattern matrix
                        unsigned char threshold = patternMatrix[row][col] * 16;
                        if (grayscale < threshold) {
                            // Set pixel to black
                            imageData[pixelIndex] = 0;
                            imageData[pixelIndex + 1] = 0;
                            imageData[pixelIndex + 2] = 0;
                        } else {
                            // Set pixel to white
                            imageData[pixelIndex] = 255;
                            imageData[pixelIndex + 1] = 255;
                            imageData[pixelIndex + 2] = 255;
                        }
                    }
                }
            }
        }
    }
}
