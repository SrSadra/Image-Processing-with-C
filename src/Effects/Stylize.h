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



int diffuseEffect(unsigned char* image, int width, int height, int channels) {
    unsigned char* blurredImage = malloc(width * height * channels);

    // Copy the original image to the blurred image
    for (int i = 0; i < width * height * channels; i++) {
        blurredImage[i] = image[i];
    }

    // Apply the diffuse filter
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sum[channels];
            for (int c = 0; c < channels; c++) {
                sum[c] = 0;
            }

            // Sum the color values of neighboring pixels
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int pixelIndex = ((y + j) * width + (x + i)) * channels;
                    for (int c = 0; c < channels; c++) {
                        sum[c] += image[pixelIndex + c];
                    }
                }
            }

            // Average the color values and set them to the blurred image
            int blurredPixelIndex = (y * width + x) * channels;
            for (int c = 0; c < channels; c++) {
                blurredImage[blurredPixelIndex + c] = sum[c] / 9;
            }
        }
    }

    // Copy the blurred image back to the original image
    for (int i = 0; i < width * height * channels; i++) {
        image[i] = blurredImage[i];
    }

    free(blurredImage);
    return 0;
}


int extrudeEffect(unsigned char* image, int width, int height, int channels,int blockSize ,int depth) {
    int newWidth = width + depth * blockSize * 2;
    int newHeight = height + depth * blockSize * 2;
    unsigned char* extrudedImage = malloc(newWidth * newHeight * channels); // Allocate memory for the extruded image

    // Initialize the extruded image as a blank canvas
    for (int i = 0; i < newWidth * newHeight * channels; i++) {
        extrudedImage[i] = 0;
    }

    // Randomize the height for each block
    srand(time(NULL)); // Seed the random number generator
    int* blockHeights = malloc(depth * sizeof(int));
    for (int i = 0; i < depth; i++) {
        blockHeights[i] = rand() % blockSize + 1; // Random height between 1 and blockSize (inclusive)
    }

    // Copy the pixels from the original image to the extruded regions
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcPixelIndex = (y * width + x) * channels;
            int dstPixelIndex = ((y + depth * blockSize) * newWidth + (x + depth * blockSize)) * channels;

            for (int b = 0; b < blockSize; b++) {
                for (int db = 0; db < depth; db++) {
                    int blockHeight = blockHeights[db];
                    for (int c = 0; c < channels; c++) {
                        if (y >= 0 && y < height && x >= 0 && x < width) {
                            extrudedImage[dstPixelIndex + b * newWidth * channels + db * blockSize * newWidth * channels + c] = image[srcPixelIndex + b * channels + c];
                        }

                        if ((y + depth + blockHeight) >= 0 && (y + depth + blockHeight) < height && x >= 0 && x < width) {
                            extrudedImage[dstPixelIndex + (depth + blockHeight + db) * newWidth * channels + b * newWidth * channels + c] = image[srcPixelIndex + b * channels + c];
                        }
                    }
                }
            }
        }
    }
    printf("alo222");

    // Copy the extruded image back to the original image
    for (int i = 0; i < width * height * channels; i++) {
        image[i] = extrudedImage[i];
    }
    printf("alo21");

    free(extrudedImage);
    free(blockHeights);
    return 0;
}



int findEdgeEffect(unsigned char* image, int width, int height, int channels) {
    // Create a copy of the original image
    unsigned char* edgeImage = malloc(width * height * channels * sizeof(unsigned char));
    for (int i = 0; i < width * height * channels; i++) {
        edgeImage[i] = image[i];
    }

    // Apply the Sobel operator to detect edges
    int sobelX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int sobelY[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < channels; c++) {
                int gradientX = 0;
                int gradientY = 0;

                // Convolve the image with the Sobel operators
                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        int pixelIndex = ((y + j) * width + (x + i)) * channels;
                        gradientX += image[pixelIndex + c] * sobelX[j + 1][i + 1];
                        gradientY += image[pixelIndex + c] * sobelY[j + 1][i + 1];
                    }
                }
                if (gradientX == 0 && gradientY == 0){
                    edgeImage[(y * width + x) * channels + c] = (unsigned  char) 255;
                }
                // Calculate the gradient magnitude
                else{
                    int gradientMagnitude = abs(gradientX) + abs(gradientY);
                    if (gradientMagnitude < 100){
                        gradientMagnitude = 255;
                    }
                    edgeImage[(y * width + x) * channels + c] = (unsigned char)gradientMagnitude;
                }

            }
        }
    }

    // Copy the edge-detected image back to the original image
    for (int i = 0; i < width * height * channels; i++) {
        image[i] = edgeImage[i];
    }

    free(edgeImage);
    return 0;
}
