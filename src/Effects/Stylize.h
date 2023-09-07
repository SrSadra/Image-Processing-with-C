#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int mynewFilter(unsigned char* image, int width, int height , int channels, int direction) {
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
    int* arr = (int *) calloc(width * height , sizeof(int));
    // Calculate the number of tiles in rows and columns
    int numCols = (width + spacing) / (tileSize + spacing) + 1;
    int numRows = (height + spacing) / (tileSize + spacing) + 1;

    // Calculate the total size of each block, including the spacing
    int blockSize = tileSize + spacing;

    // iterate over each tile
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int offsetX = rand() % (2 * spacing + 1) - spacing;
            int offsetY = rand() % (2 * spacing + 1) - spacing;

            int startX = col * blockSize + offsetX;// start coordinate of each block
            int startY = row * blockSize + offsetY;

            for (int y = 0; y < tileSize; y++) {// pixels in the tiles
                for (int x = 0; x < tileSize; x++) {
                    //coordinates of the current pixel in the image
                    int imageX = startX + x;
                    int imageY = startY + y;

                    // check if the current pixel is in the image bounds
                    if (imageX >= 0 && imageX < width && imageY >= 0 && imageY < height) {
                        arr[(imageY * width + imageX)] = 1;

                    }
                }
            }
        }
    }
    printf("alo12");
    for (int i = 0 ; i < height ; i++){ //copy image and remove between tiles
        for (int k = 0 ; k < width ; k++){
            if (arr[i * width + k] == 0 ){
                        unsigned char red = image[(i * width + k) * channels];           // Red channel
                        unsigned char green = image[(i * width + k) * channels + 1];     // Green channel
                        unsigned char blue = image[(i * width + k) * channels + 2];      // Blue channel
                        unsigned char alpha;
                        if (channels == 4) {
                            alpha = image[(i * width + k) * channels + 3];
                        }
                        image[(i * width + k) * channels] = 0;
                        image[(i * width + k) * channels + 1] = 0;
                        image[(i * width + k) * channels + 2] = 0;
                        if (channels == 4) {
                            image[(i * width + k) * channels + 3] = 0;
                        }
            }
        }
    }
    free(arr);
}



int diffuseEffect(unsigned char* image, int width, int height, int channels) {
    unsigned char* blurredImage = malloc(width * height * channels);

    for (int i = 0; i < width * height * channels; i++) {// copy the original image
        blurredImage[i] = image[i];
    }


    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sum[channels];
            for (int c = 0; c < channels; c++) {
                sum[c] = 0;
            }
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int pixelIndex = ((y + j) * width + (x + i)) * channels;
                    for (int c = 0; c < channels; c++) {
                        sum[c] += image[pixelIndex + c];
                    }
                }
            }

            int blurredPixelIndex = (y * width + x) * channels;
            for (int c = 0; c < channels; c++) {
                blurredImage[blurredPixelIndex + c] = sum[c] / 9;
            }
        }
    }

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
    // create a copy of the original image
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

int windEffect(unsigned char* image, int width, int height,int channels ,int windStrength, int windDirection){// 1 horizontal , -1 vertical

    // Temporary buffer to store the modified image
    unsigned char* tempImage = malloc(width * height * sizeof(unsigned char));

    // Apply the wind filter
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int newX, newY;
            if (windDirection == 1)
            {
                newX = (x + windStrength) % width;
                newY = y;
            }
            else
            {
                newX = x;
                newY = (y + windStrength) % height;
            }

            // Copy the pixel from the original position to the new position for each channel
            for (int c = 0; c < channels; c++)
            {
                tempImage[(newY * width + newX) * channels + c] = image[(y * width + x) * channels + c];
            }
        }
    }

    // Copy the modified image back to the original image
    for (int i = 0; i < width * height * channels; i++)
    {
        image[i] = tempImage[i];
    }
    return 0;
}


int applyEmbbossFilter(unsigned char* image, int width, int height, int channels) {
    int kernel[3][3] = {
            {-2, -1, 0},
            {-1, 1, 1},
            {0, 1, 2}
    };

    unsigned char* result = malloc(width * height * channels * sizeof(unsigned char));
    if (result == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
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

    return 0;
}


int applyOilPainting(unsigned char* image, int width, int height, int channels ,int brushSize) {//you can get the level as brushsize
    int i, j, k;
    int radius = brushSize/ 2;//brush size=5

    // Create a temporary buffer to store the modified image
    unsigned char* tempImage = (unsigned char*)malloc(width * height * channels * sizeof(unsigned char));
    if (tempImage == NULL) {
        printf("Failed to allocate memory for temporary image buffer\n");
        return 1;
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

    return 0;
}


