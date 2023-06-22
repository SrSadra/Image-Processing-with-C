#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int windEffect(unsigned char* image, int width, int height , int channels, int direction , int strength) {
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


int tilesEffect(unsigned char* image, int width, int height, int channels, int tileSize, int spacing) {
    srand(time(NULL));
    printf("31");
    int* arr = (int *) calloc(width * height , sizeof(int));
    // Calculate the number of tiles in rows and columns
    int numCols = (width + spacing) / (tileSize + spacing) + 1;
    int numRows = (height + spacing) / (tileSize + spacing) + 1;

    // Calculate the total size of each block, including the spacing
    int blockSize = tileSize + spacing;

    // Iterate over each tile
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            // Generate random offsets for each tile
            int offsetX = rand() % (2 * spacing + 1) - spacing;
            int offsetY = rand() % (2 * spacing + 1) - spacing;

            // Calculate the starting pixel coordinates of the current tile with offset
            int startX = col * blockSize + offsetX;
            int startY = row * blockSize + offsetY;
            // Process each pixel within the tile
            for (int y = 0; y < tileSize; y++) {
                for (int x = 0; x < tileSize; x++) {
                    // Calculate the coordinates of the current pixel within the image
                    int imageX = startX + x;
                    int imageY = startY + y;

                    // Check if the current pixel is within the image bounds
                    if (imageX >= 0 && imageX < width && imageY >= 0 && imageY < height) {
                        arr[(imageY * width + imageX)] = 1;

                    }
                }
            }
        }
    }
    printf("alo12");
    for (int i = 0 ; i < height ; i++){
        for (int k = 0 ; k < width ; k++){
            if (arr[i * width + k] == 0 ){
                        unsigned char red = image[(i * width + k) * channels];           // Red channel
                        unsigned char green = image[(i * width + k) * channels + 1];     // Green channel
                        unsigned char blue = image[(i * width + k) * channels + 2];      // Blue channel
                        unsigned char alpha;
                        if (channels == 4) {
                            alpha = image[(i * width + k) * channels + 3];
                        }
                        // Perform operations on each channel separately
                        // Example: Invert the color of each channel
                        image[(i * width + k) * channels] = 255 - red;
                        image[(i * width + k) * channels + 1] = 255 - green;
                        image[(i * width + k) * channels + 2] = 255 - blue;
                        if (channels == 4) {
                            image[(i * width + k) * channels + 3] = 255 - alpha;
                        }
            }
        }
    }
    free(arr);
}
