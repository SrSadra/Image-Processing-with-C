#include <stdio.h>
#include <stdlib.h>

void crop_image(unsigned char *image, int width, int height, int x1, int y1, int x2, int y2)
{
    unsigned char *cropped_image;
    int i, j;

    // Allocate memory for the cropped image
    cropped_image = (unsigned char *)malloc((x2 - x1) * (y2 - y1) * 3);
    if (cropped_image == NULL)
    {
        printf("Error: Could not allocate memory for cropped image\n");
        return;
    }

    // Copy the pixels from the original image to the cropped image
    for (i = y1; i < y2; i++)
    {
        for (j = x1; j < x2; j++)
        {
            cropped_image[(i - y1) * (x2 - x1) * 3 + (j - x1) * 3 + 0] = image[i * width * 3 + j * 3 + 0];
            cropped_image[(i - y1) * (x2 - x1) * 3 + (j - x1) * 3 + 1] = image[i * width * 3 + j * 3 + 1];
            cropped_image[(i - y1) * (x2 - x1) * 3 + (j - x1) * 3 + 2] = image[i * width * 3 + j * 3 + 2];
        }
    }

    // Write the cropped image to a file
    FILE *fp;
    fp = fopen("output.bmp", "wb");
    if (fp == NULL)
    {
        printf("Error: Could not open output file\n");
        free(cropped_image);
        return;
    }

    fwrite(cropped_image, sizeof(unsigned char), (x2 - x1) * (y2 - y1) * 3, fp);

//    // Free memory and close files
//    free(cropped_image);
//    fclose(fp);
}

int main()
{
    FILE *fp;
    unsigned char *image;
    int width, height,chanel;
    int x1, y1, x2, y2;

    // Open the input file
    fp = fopen("input.bmp", "rb");
    if (fp == NULL)
    {
        printf("Error: Could not open input file\n");
        return 1;
    }

    // Read the BMP header
    fseek(fp, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);

    // Allocate memory for the input image
    image = (unsigned char *)malloc(width * height * chanel);
    if (image == NULL)
    {
        printf("Error: Could not allocate memory for input image\n");
        fclose(fp);
        return 1;
    }

    // Read the input image
    fseek(fp, 54, SEEK_SET);
    fread(image, sizeof(unsigned char), width * height * 3, fp);

    // Set the cropping coordinates
    x1 = 100;
    y1 = 100;
    x2 = 200;
    y2 = 200;

    crop_image(image,width,height,x1,y1,x2,y2);

    free(image);

    return 0;
}
