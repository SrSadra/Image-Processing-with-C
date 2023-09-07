#include <stdio.h>

// void makecolor(unsigned char * image ,unsigned char color , int i , int width , int height , int channels){
//     for (int i = 0; i < width * height * channels; i += channels) {
//         // unsigned char r = image[i];
//         // unsigned char g = image[i + 1];
//         // unsigned char b = image[i + 2];
//         image[i] = color;
//     }
// }

int makeGray(unsigned char* image, int width, int height, int channels) {
    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char r = image[i];
        unsigned char g = image[i + 1];
        unsigned char b = image[i + 2];
//        printf("%c %c %c\n" , r , g  , b);
        unsigned char gray = (unsigned char)(0.2989 * r + 0.5870 * g + 0.1140 * b);
        image[i] = gray;
        image[i + 1] = gray;
        image[i + 2] = gray;
    }
    return 0;
}

void brightness(unsigned char * image , int width , int height , int channels , float percent ){
    int brightVal = width * height * channels;
    float brightPer = 1.0 + (percent / 100);

    for (int i  = 0 ; i < brightVal ; i++){
        float tmp = brightPer * image[i];

        // range of brighness is between 0 & 255
        if (tmp < 0){
            image[i] = 0;
        }
        else if (tmp > 0){
            image[i] = 255;
        }
        else {
            image[i] = (unsigned char) tmp;
        }
    }
}



void rgbToHsl(unsigned char r, unsigned char g, unsigned char b, float* h, float* s, float* l) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float maxVal = fmaxf(rf, fmaxf(gf, bf));
    float minVal = fminf(rf, fminf(gf, bf));

    *l = (maxVal + minVal) / 2.0f;

    if (maxVal == minVal) {
        *h = 0.0f;
        *s = 0.0f;
    } else {
        float delta = maxVal - minVal;

        *s = (*l <= 0.5f) ? (delta / (maxVal + minVal)) : (delta / (2.0f - maxVal - minVal));

        if (maxVal == rf) {
            *h = (gf - bf) / delta + (gf < bf ? 6.0f : 0.0f);
        } else if (maxVal == gf) {
            *h = (bf - rf) / delta + 2.0f;
        } else {
            *h = (rf - gf) / delta + 4.0f;
        }

        *h /= 6.0f;
    }
}

unsigned char hueToRgb(float p, float q, float t) {
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;

    if (t < 1.0f / 6.0f)
        return (unsigned char)((p + (q - p) * 6.0f * t) * 255.0f);
    if (t < 1.0f / 2.0f)
        return (unsigned char)(q * 255.0f);
    if (t < 2.0f / 3.0f)
        return (unsigned char)((p + (q - p) * (2.0f / 3.0f - t) * 6.0f) * 255.0f);

    return (unsigned char)(p * 255.0f);
}

void hslToRgb(float h, float s, float l, unsigned char* r, unsigned char* g, unsigned char* b) {
    if (s == 0.0f) {
        *r = *g = *b = (unsigned char)(l * 255.0f);
    } else {
        float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
        float p = 2.0f * l - q;

        *r = hueToRgb(p, q, h + 1.0f / 3.0f);
        *g = hueToRgb(p, q, h);
        *b = hueToRgb(p, q, h - 1.0f / 3.0f);
    }
}


int applyHslAdjustment(unsigned char* image, int width, int height,int channels ,float hue, float saturation, float lightness) {
    for (int i = 0; i < width * height; i++) {
        unsigned char r = image[i * channels];
        unsigned char g = image[i * channels + 1];
        unsigned char b = image[i * channels + 2];

        float h, s, l;
        rgbToHsl(r, g, b, &h, &s, &l);

        hue = fmin(180.0f, fmax(-180.0f, hue));
        saturation = fmin(100.0f, fmax(-100.0f, saturation));
        lightness = fmin(100.0f, fmax(-100.0f, lightness));

        hue = (hue + 180.0f) / 360.0f;
        saturation = 1.0f + (saturation / 100.0f);
        lightness = (lightness + 100.0f) / 200.0f;

        // Apply hue adjustment
        h += hue;
        if (h < 0.0f) h += 1.0f;
        if (h > 1.0f) h -= 1.0f;

        // Apply saturation adjustment
        s *= saturation;

        // Apply lightness adjustment
        l += lightness;
        if (l < 0.0f) l = 0.0f;
        if (l > 1.0f) l = 1.0f;

        // Convert back to RGB
        hslToRgb(h, s, l, &r, &g, &b);

        image[i * channels] = r;
        image[i * channels + 1] = g;
        image[i * channels + 2] = b;
    }
    return 0;
}


int applySepiaFilter(unsigned char* image, int width, int height, int channels) {
    for (int i = 0; i < width * height; i++) {
        unsigned char* pixel = image + (i * channels);

        unsigned char originalRed = pixel[0];
        unsigned char originalGreen = pixel[1];
        unsigned char originalBlue = pixel[2];

        // Define the tolerance range for colors near white and yellow
        int whiteTolerance = 95;
        int yellowTolerance = 33;

        // Check if the pixel is within the tolerance range of white or yellow
        if ((originalRed > 255 - whiteTolerance && originalGreen > 255 - whiteTolerance && originalBlue > 255 - whiteTolerance) ||
            (originalRed > 255 - yellowTolerance && originalGreen > 255 - yellowTolerance)) {
            // Skip applying the sepia filter to near-white and near-yellow pixels
            continue;
        }

        unsigned char newRed = (unsigned char)((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
        unsigned char newGreen = (unsigned char)((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
        unsigned char newBlue = (unsigned char)((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));

        pixel[0] = newRed;
        pixel[1] = newGreen;
        pixel[2] = newBlue;

        if (channels == 4) {
            // Handle alpha channel if the image has one
            unsigned char originalAlpha = pixel[3];
            pixel[3] = originalAlpha;
        }
    }

    return 0;
}






