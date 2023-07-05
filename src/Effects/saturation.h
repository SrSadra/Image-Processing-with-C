#include <stdio.h>
#include <math.h>
void applySaturationFilter(unsigned char* image, int width, int height, int channels) {
    double saturation = 1.5; // Hardcoded saturation value you can get it as an input
    for (int i = 0; i < width * height; i++) {
        unsigned char originalRed = image[i * channels];
        unsigned char originalGreen = image[i * channels + 1];
        unsigned char originalBlue = image[i * channels + 2];

        // Convert RGB to HSL
        double r = originalRed / 255.0;
        double g = originalGreen / 255.0;
        double b = originalBlue / 255.0;

        double max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
        double min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
        double l = (max + min) / 2.0;

        double s;
        if (max == min) {
            s = 0.0;
        } else if (l <= 0.5) {
            s = (max - min) / (max + min);
        } else {
            s = (max - min) / (2.0 - max - min);
        }

        // Modify saturation
        s *= saturation;

        // Convert HSL back to RGB
        double chroma = (1.0 - fabs(2.0 * l - 1.0)) * s;
        double h = 0.0;
        if (s != 0.0) {
            if (max == r) {
                h = fmod((g - b) / chroma, 6.0);
            } else if (max == g) {
                h = ((b - r) / chroma) + 2.0;
            } else {
                h = ((r - g) / chroma) + 4.0;
            }
        }
        h *= 60.0;

        double x = chroma * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
        double r1, g1, b1;

        if (h >= 0.0 && h < 60.0) {
            r1 = chroma;
            g1 = x;
            b1 = 0.0;
        } else if (h >= 60.0 && h < 120.0) {
            r1 = x;
            g1 = chroma;
            b1 = 0.0;
        } else if (h >= 120.0 && h < 180.0) {
            r1 = 0.0;
            g1 = chroma;
            b1 = x;
        } else if (h >= 180.0 && h < 240.0) {
            r1 = 0.0;
            g1 = x;
            b1 = chroma;
        } else if (h >= 240.0 && h < 300.0) {
            r1 = x;
            g1 = 0.0;
            b1 = chroma;
        } else {
            r1 = chroma;
            g1 = 0.0;
            b1 = x;
        }

        double m = l - (chroma / 2.0);
        double finalRed = (r1 + m) * 255.0;
        double finalGreen = (g1 + m) * 255.0;
        double finalBlue = (b1 + m) * 255.0;
        // Clamp the values to the range [0, 255]
        unsigned char newRed = (unsigned char)((finalRed > 255.0) ? 255.0 : ((finalRed < 0.0) ? 0.0 : finalRed));
        unsigned char newGreen = (unsigned char)((finalGreen > 255.0) ? 255.0 : ((finalGreen < 0.0) ? 0.0 : finalGreen));
        unsigned char newBlue = (unsigned char)((finalBlue > 255.0) ? 255.0 : ((finalBlue < 0.0) ? 0.0 : finalBlue));

        // Update the image data with the modified RGB values
        image[i * channels] = newRed;
        image[i * channels + 1] = newGreen;
        image[i * channels + 2] = newBlue;
    }
}