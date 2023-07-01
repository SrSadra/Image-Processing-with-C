#include <stdio.h>
#include "File.h"
#include "Image.h"
#include "Effects\\Noise.h"
#include "Effects\\Color.h"
#include "Effects\\sepia.h"
#include "Effects\\vignette.h"
#include "Effects\\oilpaint.h"
#include "Effects\\gaussianblur.h"
#include "Effects\\emboss.h"
#include "Effects\\solarize.h"
#include "Save.h"

#define imageSize 1000000
#define strSize 1000

 struct Image* img;



void saveHandler(){
    printf("choose destination path: (0 for skip)");
    // scanf destination
    char* inp =(char*) malloc(strSize);//?
    scanf("%s" , inp);
    printf("select type to save\n1. JPEG\n2. PNG\n");
    int inpType;
    scanf("%d", &inpType);
    switch (inpType){
        case 1:;
            int quality;
            printf("Enter Image Quality: ");
            scanf("%d", &quality);
//        saveImageAsJPEG(inp , img->bytes, img->width , img->height , img->channels , quality);
            break;
        case 2:
        saveImageAsPNG(inp , img->bytes , img->width , img->height , img->channels);
        case 3:
            saveBitmap(inp , img->bytes , img->width , img->height);
            printf("comp");
            break;
    }
    free(img);

}

void effectHandler(){
    int input;
    int flg = 0;
    while (1){
        printf("-%d", input);
        scanf("%d", &input);
        switch(input){
            // color costumization
            case 1:
                // which color costum 1 - make gray
                scanf("%d", &input);
                if (input == 1){
                    printf("alo222\n");
                    int check = makeGray(img->bytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("gray sucsessfuly added!");
                    }
                }
                // costum 2 - brightness
                else if (input == 2){
                    float percent;
                    printf("Enter Brighness percentage: ");
                    scanf("%f" , &percent);
                    brightness(img->bytes , img->width , img->height , img->channels , percent);
                }
                else if (input == 3){
                    applySepiaFilter(img->bytes , img->width , img->height);
                }
                else if (input == 4){
                    apply_vignette(img->bytes ,img->width , img->height ,img->channels);
                }
                else if (input == 5){
                    applyOilPaintingFilter(img->bytes , img->width , img->height,img->channels);
                }
                else if (input ==6){
                    applyGaussianBlurFilter(img->bytes , img->width , img->height,img->channels);
                }
                else if (input ==7){
                    applyEmbbossFilter(img->bytes , img->width , img->height,img->channels);
                }
                else if (input ==8){
                    applySolarizeFilter(img->bytes , img->width , img->height,img->channels);
                }
                else {
                    printf("Invalid Input");
                    flg = 0;
                }

                break;
                // add noise
            case 2:
                scanf("%d", &input);
                if (input == 1){
                    int percent;
                    printf("Enter Amount of noise (0 , 400): ");
                    scanf("%d", &percent);
                    addNoise(img->bytes , img->width , img->height , percent);
                    printf("noise sucsessfuly added");
                }

                break;
            case 3:

                break;
            case 4: //exit

                return;
                break;
            default:
                printf("Invalid Input");
        }
    }

}

void fileHandler(int input){
    printf("3");
    img = (struct Image *) malloc(sizeof(struct Image) * imageSize);

    switch (input){
        case 1:;
            char* path = (char*) malloc(strSize);
            scanf("%s", path);
            img->bytes = readfile( &(img->width) , &(img->height) , &(img->channels) , path );
            img->type = 1;
            img->path = path;
            free(path);
            break;
        case 2:
            break;
    }
}


void userHandler(){
    static int input;
    while (1){
        // welcome menu
        // choose option
        printf("Enter Input Method\n1. Local File\n2. URL\n3. Gmail");
        scanf("%d", &input);
        fileHandler(input);
        printf("alo2");
        // which Effect category
        effectHandler();

        // destination path
        saveHandler();
        break;// temporary


    }
}

// struct Image * imageHandler(){
//     struct Image img;
// }

