#include <stdio.h>

typedef struct {
    unsigned char red, green, blue;
} Pixel;

typedef struct {
    int width, height;
    Pixel* data;
} Image;

Image* loadImage(const char* filename) {
    // Code to load image data into Image struct
    // ...

    return image;
}

void saveImage(const char* filename, Image* image) {
    // Code to save Image data to file
    // ...
}

void applySepiaFilter(Image* image) {
    int i;
    for (i = 0; i < image->width * image->height; i++) {
        unsigned char originalRed = image->data[i].red;
        unsigned char originalGreen = image->data[i].green;
        unsigned char originalBlue = image->data[i].blue;

        unsigned char newRed = (unsigned char)((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
        unsigned char newGreen = (unsigned char)((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
        unsigned char newBlue = (unsigned char)((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));

        image->data[i].red = newRed;
        image->data[i].green = newGreen;
        image->data[i].blue = newBlue;
    }
}

int main() {
    // Load image
    Image* image = loadImage("input.bmp");
    if (!image) {
        printf("Error loading the image.\n");
        return 1;
    }

    // Apply sepia filter
    applySepiaFilter(image);

    // Save image
    saveImage("output.bmp", image);

    // Cleanup
    // ...

    return 0;
}

