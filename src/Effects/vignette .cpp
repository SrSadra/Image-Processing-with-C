#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define VIGNETTE_STRENGTH 0.5

typedef struct {
    unsigned char red, green, blue;
} Pixel;

void apply_vignette(Pixel* image) {
    int center_x = IMAGE_WIDTH / 2;
    int center_y = IMAGE_HEIGHT / 2;
    double max_distance = sqrt(center_x * center_x + center_y * center_y);

    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            int index = y * IMAGE_WIDTH + x;
            double distance = sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
            double intensity = 1.0 - (distance / max_distance) * VIGNETTE_STRENGTH;

            image[index].red = (unsigned char)(image[index].red * intensity);
            image[index].green = (unsigned char)(image[index].green * intensity);
            image[index].blue = (unsigned char)(image[index].blue * intensity);
        }
    }
}

int main() {
    // Assuming you have an image stored in a Pixel array
    Pixel* image = (Pixel*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(Pixel));

    // Apply the vignette effect
    apply_vignette(image);

    // Rest of the code...

    free(image); // Don't forget to free the memory

    return 0;
}
