#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int applyCrystalizeFilter(unsigned char* image, int width, int height, int channels, int cellSize)
{
    int numCellsX = ceil((double)width / cellSize);
    int numCellsY = ceil((double)height / cellSize);
    int numCells = numCellsX * numCellsY;

    unsigned char* output = malloc(width * height * channels * sizeof(unsigned char));

    // Generate a random seed
    srand(time(NULL));

    for (int cellY = 0; cellY < numCellsY; cellY++) {
        for (int cellX = 0; cellX < numCellsX; cellX++) {
            int cellOffsetX = (cellX % 2) * cellSize / 2;  // Offset for even/odd rows
            int startX = cellX * cellSize - cellOffsetX;
            int startY = cellY * cellSize;

            int endX = startX + cellSize;
            int endY = startY + cellSize;

            if (endX > width) endX = width;
            if (endY > height) endY = height;

            // Generate random offsets for irregular shapes
            int offsetX = rand() % cellSize;
            int offsetY = rand() % cellSize;

            int cellSum[channels];
            int numPixels = 0;

            // Initialize cellSum array
            for (int c = 0; c < channels; c++) {
                cellSum[c] = 0;
            }

            for (int y = startY; y < endY; y++) {
                for (int x = startX; x < endX; x++) {
                    int offsetXed = x - startX + offsetX;
                    int offsetYed = y - startY + offsetY;
                    int dist = abs(offsetXed - cellSize / 2) + abs(offsetYed - cellSize / 2);

                    if (dist <= cellSize / 2) {
                        for (int c = 0; c < channels; c++) {
                            int pixelIndex = (y * width + x) * channels + c;
                            cellSum[c] += image[pixelIndex];
                        }
                        numPixels++;
                    }
                }
            }

            for (int y = startY; y < endY; y++) {
                for (int x = startX; x < endX; x++) {
                    int offsetXed = x - startX + offsetX;
                    int offsetYed = y - startY + offsetY;
                    int dist = abs(offsetXed - cellSize / 2) + abs(offsetYed - cellSize / 2);

                    if (dist <= cellSize / 2) {
                        for (int c = 0; c < channels; c++) {
                            int pixelIndex = (y * width + x) * channels + c;
                            output[pixelIndex] = cellSum[c] / numPixels;
                        }
                    }
                }
            }
        }
    }

    // Copy the output back to the original image
    for (int i = 0; i < width * height * channels; i++) {
        image[i] = output[i];
    }

    free(output);

    return 0;
}


int applyHalftone(unsigned char* image,int width,int height,int channels ) {
    unsigned char* imageData = image;
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

    return 0;
}




int applyMosaicFilter(unsigned char* image, int width, int height, int channels, int blockSize) {
    // Iterate over each block in the image
    for (int y = 0; y < height; y += blockSize) {
        for (int x = 0; x < width; x += blockSize) {
            // Calculate the average color values for the block
            int sumRed = 0, sumGreen = 0, sumBlue = 0 , sumAlpha=0;
            int count = 0;

            for (int dy = 0; dy < blockSize && y + dy < height; dy++) {
                for (int dx = 0; dx < blockSize && x + dx < width; dx++) {
                    int pixelIndex = ((y + dy) * width + (x + dx)) * channels;
                    sumRed += image[pixelIndex];
                    sumGreen += image[pixelIndex + 1];
                    sumBlue += image[pixelIndex + 2];
                    if(channels == 4){
                        sumAlpha+=image[pixelIndex + 3];
                    }
                    count++;
                }
            }

            // Calculate the average color values
            unsigned char averageRed = (unsigned char)(sumRed / count);
            unsigned char averageGreen = (unsigned char)(sumGreen / count);
            unsigned char averageBlue = (unsigned char)(sumBlue / count);
            unsigned char averageAlpha = (unsigned char)(sumAlpha / count);

            // Set the color of each pixel in the block to the average color
            for (int dy = 0; dy < blockSize && y + dy < height; dy++) {
                for (int dx = 0; dx < blockSize && x + dx < width; dx++) {
                    int pixelIndex = ((y + dy) * width + (x + dx)) * channels;
                    image[pixelIndex] = averageRed;
                    image[pixelIndex + 1] = averageGreen;
                    image[pixelIndex + 2] = averageBlue;
                    image[pixelIndex + 2] = averageAlpha;
                }
            }
        }
    }

    return 0;
}