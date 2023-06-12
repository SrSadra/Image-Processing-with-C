#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addNoise(unsigned char* image, int width, int height, int amount) {
    srand(time(NULL));
    float minIntensity = 0.1;   // Minimum amount
    float maxIntensity = 400.0; // Maximum amount

    float scaledIntensity = minIntensity + (amount * (maxIntensity - minIntensity));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            int noise = (rand() % (2 * amount)) - amount;
            int pixel = image[index] + noise;
            printf("%d %d\n" , index , pixel);
            if (pixel < 0)
                pixel = 0;
            else if (pixel > 250)
                pixel = 250;

            image[index] = pixel;
        }
    }
}









