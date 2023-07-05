#include <stdio.h>
void applySepiaFilter(unsigned char* image, int width, int height, int channels) {
    for (int i = 0; i < width * height; i++) {
        unsigned char originalRed = image[i * channels];
        unsigned char originalGreen = image[i * channels + 1];
        unsigned char originalBlue = image[i * channels + 2];

        unsigned char newRed = (unsigned char)((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
        unsigned char newGreen = (unsigned char)((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
        unsigned char newBlue = (unsigned char)((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));

        image[i * channels] = newRed;
        image[i * channels + 1] = newGreen;
        image[i * channels + 2] = newBlue;

        // For RGBA images, set the alpha channel to its original value
        if (channels == 4) {
            unsigned char originalAlpha = image[i * channels + 3];
            image[i * channels + 3] = originalAlpha;
        }
    }
}

