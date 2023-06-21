#include <stdio.h>

void applySepiaFilter(unsigned char* image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        unsigned char originalRed = image[i * 3];
        unsigned char originalGreen = image[i * 3 + 1];
        unsigned char originalBlue = image[i * 3 + 2];

        unsigned char newRed = (unsigned char)((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
        unsigned char newGreen = (unsigned char)((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
        unsigned char newBlue = (unsigned char)((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));

        image[i * 3] = newRed;
        image[i * 3 + 1] = newGreen;
        image[i * 3 + 2] = newBlue;
    }
}



