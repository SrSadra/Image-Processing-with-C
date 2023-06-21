#include <stdio.h>
#include <stdlib.h>

// Function to apply Gaussian blur to an image
void applyGaussianBlur(unsigned char* image, int width, int height) {
    int kernel[5][5] = {
            {1, 4, 7, 4, 1},
            {4, 16, 26, 16, 4},
            {7, 26, 41, 26, 7},
            {4, 16, 26, 16, 4},
            {1, 4, 7, 4, 1}
    };

    // Create a temporary buffer to hold the blurred image
    unsigned char* blurredImage = malloc(width * height * sizeof(unsigned char));

    // Iterate over each pixel in the image
    for (int y = 2; y < height - 2; y++) {
        for (int x = 2; x < width - 2; x++) {
            int sum = 0;

            // Apply the kernel to the neighborhood of the pixel
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    sum += image[(y + i) * width + (x + j)] * kernel[i + 2][j + 2];
                }
            }

            // Normalize and assign the blurred pixel value
            blurredImage[y * width + x] = sum / 273;  // Dividing by the sum of kernel values (273 in this case)
        }
    }

    // Copy the blurred image back to the input image buffer
    memcpy(image, blurredImage, width * height * sizeof(unsigned char));

    // Free the memory allocated for the temporary buffer
    free(blurredImage);
}
//
//int main() {
//    const int width = 640;
//    const int height = 480;
//
//    // Create an image buffer and initialize it with test data
//    unsigned char* image = malloc(width * height * sizeof(unsigned char));
//    for (int i = 0; i < width * height; i++) {
//        image[i] = i % 256;  // Just an example, you should load the image data from a file or another source
//    }
//
//    // Apply Gaussian blur to the image
//    applyGaussianBlur(image, width, height);
//
//    // Display or save the blurred image
//    // ...
//
//    // Free the memory allocated for the image buffer
//    free(image);
//
//    return 0;
//}
