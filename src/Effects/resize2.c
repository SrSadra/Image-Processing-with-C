//#include <stdio.h>
//#include <stdlib.h>
//
//// Function to resize an image
//void resizeImage(int* image, int width, int height, int new_width, int new_height) {
//    // Create a new array to store the resized image
//    int* resizedImage = (int*)malloc(new_width * new_height * sizeof(int));
//
//    // Calculate the scaling factors for width and height
//    float widthScale = (float)new_width / width;
//    float heightScale = (float)new_height / height;
//
//    // Loop through each pixel of the resized image
//    for (int y = 0; y < new_height; y++) {
//        for (int x = 0; x < new_width; x++) {
//            // Calculate the corresponding pixel position in the original image
//            int srcX = (int)(x / widthScale);
//            int srcY = (int)(y / heightScale);
//
//            // Get the pixel value from the original image
//            int srcIndex = srcY * width + srcX;
//            int pixel = image[srcIndex];
//
//            // Set the pixel value in the resized image
//            int dstIndex = y * new_width + x;
//            resizedImage[dstIndex] = pixel;
//        }
//    }//cancel va okay badan
//
//    // Free the memory allocated for the original image
//    //free(image);
//
//    // Use the resized image for further processing
//    // ...
//
//    // Free the memory allocated for the resized image
//    //free(resizedImage);
//}
//
///*int main() {
//    // Assume you have an image represented as a 2D array of pixels
//    int imageWidth = 800;//input
//    int imageHeight = 600;//input
//    int* image ;//= (int*)malloc(imageWidth * imageHeight * sizeof(int));
//    // Call the resizeImage function with the desired new width and height
//    int newWidth = 400;//input
//    int newHeight = 300;//input
//    resizeImage(image, imageWidth, imageHeight, newWidth, newHeight);
//
//    return 0;
//}*/
#include <stdio.h>
#include <stdlib.h>

void resizeImage(char *inputFile, char *outputFile, int width, int height) {
    FILE *fp = fopen(inputFile, "rb");
    FILE *fp2 = fopen(outputFile, "wb");

    // Read header
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fp);

    // Get width and height
    int oldWidth = *(int *)&header[18];
    int oldHeight = *(int *)&header[22];

    // Allocate memory for new image
    unsigned char *data = (unsigned char *)malloc(oldWidth * oldHeight * 3);
    unsigned char *newData = (unsigned char *)malloc(width * height * 3);

    // Read data
    fread(data, sizeof(unsigned char), oldWidth * oldHeight * 3, fp);

    // Calculate scaling factors
    float xFactor = (float)oldWidth / (float)width;
    float yFactor = (float)oldHeight / (float)height;

    // Loop through each pixel in new image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate corresponding position in original image
            int oldX = (int)(x * xFactor);
            int oldY = (int)(y * yFactor);

            // Copy pixel value from original image to new image
            newData[(y * width + x) * 3] = data[(oldY * oldWidth + oldX) * 3];
            newData[(y * width + x) * 3 + 1] = data[(oldY * oldWidth + oldX) * 3 + 1];
            newData[(y * width + x) * 3 + 2] = data[(oldY * oldWidth + oldX) * 3 + 2];
        }
    }

    // Write header
    fwrite(header, sizeof(unsigned char), 54, fp2);//?

    // Write data
    fwrite(newData, sizeof(unsigned char), width * height * 3, fp2);//?

    fclose(fp);
    fclose(fp2);
}

int main() {
    resizeImage("input.bmp", "output.bmp", 640, 480);
    return 0;
}
