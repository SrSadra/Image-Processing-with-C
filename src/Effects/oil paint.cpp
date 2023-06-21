#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH  640
#define HEIGHT 480
#define RADIUS 5
#define INTENSITY_LEVELS 256

typedef struct {
    unsigned char r, g, b;
} Pixel;

void oilPaintEffect(Pixel** image, int width, int height) {
    int x, y, i, j;
    int intensityCount[INTENSITY_LEVELS] = {0};
    Pixel** blurredImage = malloc(height * sizeof(Pixel*));

    for (y = 0; y < height; y++) {
        blurredImage[y] = malloc(width * sizeof(Pixel));
        for (x = 0; x < width; x++) {
            intensityCount[0] = {0};

            // Calculate the intensity levels of nearby pixels within the radius
            for (i = -RADIUS; i <= RADIUS; i++) {
                for (j = -RADIUS; j <= RADIUS; j++) {
                    int nx = x + i;
                    int ny = y + j;

                    // Ensure the pixel coordinates are within the image bounds
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        unsigned char intensity = (image[ny][nx].r + image[ny][nx].g + image[ny][nx].b) / 3;
                        intensityCount[intensity]++;
                    }
                }
            }

            int maxCount = 0;
            int maxIntensity = 0;

            // Find the intensity level with the maximum count
            for (i = 0; i < INTENSITY_LEVELS; i++) {
                if (intensityCount[i] > maxCount) {
                    maxCount = intensityCount[i];
                    maxIntensity = i;
                }
            }

            // Set the pixel value to the color with the most occurrences in the neighborhood
            blurredImage[y][x].r = maxIntensity;
            blurredImage[y][x].g = maxIntensity;
            blurredImage[y][x].b = maxIntensity;
        }
    }

    // Copy the blurred image back to the original image
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            image[y][x] = blurredImage[y][x];
        }
        free(blurredImage[y]);
    }

    free(blurredImage);
}

int main() {
    // Example usage
    Pixel** image = malloc(HEIGHT * sizeof(Pixel*));
    int x, y;

    for (y = 0; y < HEIGHT; y++) {
        image[y] = malloc(WIDTH * sizeof(Pixel));
        for (x = 0; x < WIDTH; x++) {
            // Set pixel values (dummy values for demonstration)
            image[y][x].r = rand() % 256;
            image[y][x].g = rand() % 256;
            image[y][x].b = rand() % 256;
        }
    }

    // Apply the oil paint effect to the image
    oilPaintEffect(image, WIDTH, HEIGHT);

    // Display the modified image
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            printf("(%d, %d, %d) ", image[y][x].r, image[y][x].g, image[y][x].b);
        }
        printf("\n");
    }

    // Cleanup: Free allocated memory
    for (y = 0; y < HEIGHT; y++) {
        free(image[y]);
    }
    free(image);

    return 0;
}
