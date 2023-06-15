#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addNoise(unsigned char* image, int width, int height ,int amount , int channels) {
//    srand(time(NULL));
//
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            int index = (y * width + x) * channels;
//
//            // Add noise to each color channel (R, G, B)
//            for (int channel = 0; channel < channels; channel++) {
//                int noise = (rand() % (2 * amount)) - amount;
//                int pixel = image[index + channel] + noise;
//
//                if (pixel < 0)
//                    pixel = 0;
//                else if (pixel > 255)
//                    pixel = 255;
//
//                image[index + channel] = (unsigned char) pixel;
//            }
//        }
//    }
}