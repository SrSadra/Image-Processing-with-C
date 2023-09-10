#include <stdio.h>
#include <stdlib.h>
#include "File.h"
#include "Image.h"
#include "Effects\\Noise.h"
#include "Effects\\Color.h"
#include "Effects\\Redeye.h"
#include "Effects\\Stylize.h"
#include "Effects\\Pixelate.h"
#include "Effects\\CartoonDrawing.h"
#include "Effects\\Blur.h"
#include "Effects\\Border.h"
#include "Effects\\Solarize.h"
#include "Save.h"
#include "email.h"
#include "Menu.h"
#include "popupImage.h"

//
#define imageSize 1000000
#define strSize 1000

struct Image* img;

int fileLocal(char* path , int type){
    if (setFormat(path , &(img->format)) == -1) {
        printf("Invalid format!");
        return 1;
    }
    img->bytes = readfile( &(img->width) , &(img->height) , &(img->channels) , path , img->format );
    if (img->bytes == NULL){
        printf("Invalid file!");
        return 2;

    }
    img->type = type;
    img->path = (char *) malloc(strSize * sizeof(char));
    memcpy(img->path , path , strSize * sizeof(char));
    free(path);
    return 0;
}

void saveHandler(){
    int flg = 0;
    printf("choose destination path: (0 for skip & dont add format for it)");
    // scanf destination
    char* inp =(char*) malloc(strSize);//?
    int inpType;
    scanf("%s" , inp);
    if (!strcmp(inp , "0")){
        inp = img->path;
        flg = 1;
    }
    if (img->channels == 3){
        if (flg == 0){
            strcat(inp , ".jpg");
        }
        inpType =1;
    }
    else if (img->channels == 4){
        if (flg == 0){
            strcat( inp , ".png");
        }
        inpType = 2;
    }
    else{
        printf("Invalid format");
    }
    printf("%s", inp);

    switch (inpType){
        case 1:;
            int quality;
            printf("Enter Image Quality: ");
            scanf("%d", &quality);
            saveImageAsJPEG(inp , img->bytes, img->width , img->height , img->channels , quality);
            break;
        case 2:
            saveImageAsPNG(inp , img->bytes , img->width , img->height , img->channels);
            break;
        case 3:
            saveBitmap(inp , img->bytes , img->width , img->height , img->channels);
            break;
        case 4:
            saveStbi(img->bytes , inp , img->width , img->height , img->channels);
    }
    free(inp);
    free(img);

}

void effectHandler(){
    int input;
    while (1){
        fflush(stdin);
        unsigned char* tmpBytes = copyImage(img);
        printf("Filters\n1-color costumization\n2-Noise\n3-Red Eye(in process)\n4-Stylize\n5-Cartoon & Drawing\n6-Blur\n7-Pixelate\n8-Solarize\n9-Borders\n0-Exit");
        scanf("%d", &input);
        switch(input){
            case 1:// color costumization
                printf("Color Costumization:\n1-Make Gray\n2-Brightness\n3-Hue Adjustment\n4-Sepia");
                scanf("%d", &input);

                // which color costum 1 - make gray
                if (input == 1){
                    int check = makeGray(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("gray sucsessfuly added!");
                    }
                }
                    // costum 2 - brightness
                else if (input == 2){
                    float percent;
                    printf("Enter Brighness percentage: ");
                    scanf("%f" , &percent);
                    brightness(tmpBytes , img->width , img->height , img->channels , percent);
                }
                    // costum 3 - hue adjustment
                else if (input == 3){
                    float heuInp , saturationInp , lightnessInp;
                    printf("Enter hue in range -180 to 180: ");
                    scanf("%f" , &heuInp);
                    printf("Enter saturation in range -100 to 100: ");
                    scanf("%f" , &saturationInp);
                    printf("Enter lightness in range -100 to 100: ");
                    scanf("%f" , &lightnessInp);
                    int check = applyHslAdjustment(tmpBytes , img->width , img->height , img->channels , heuInp , saturationInp , lightnessInp);
                    if (check == 0){
                        printf("Hsl applied");
                    }
                }
                else if (input == 4){
                    int check=applySepiaFilter(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Sepia sucsessfuly added");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 2: //add noise
                printf("Noise:\n1-Noise");
                scanf("%d", &input);
                if (input == 1){
                    int percent;
                    printf("Enter Amount of noise (0 , 400): ");
                    scanf("%d", &percent);
                    addNoise(tmpBytes , img->width , img->height  , percent , img->channels);
                    printf("noise sucsessfuly added");
                }
                break;
            case 3:
                scanf("%d", &input);
                if (input == 1){
                    int check = removeRedEye(tmpBytes , img->width , img->height , img->channels );
                    if (check == 0){// modify check before graphic
                        printf("Red Eye reduced");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 4:
                printf("Stylize:\n1-myNewFilter\n2-tiles\n3-diffuse\n5-find Edge\n6-wind (in process)\n7-Emboss\n8-Oil Painting");
                scanf("%d" , &input);
                if (input == 1){
                    int direction , strength;
                    printf("Enter Wind direction (0 and 1): ");
                    scanf("%d" , &direction);
                    int check = mynewFilter(tmpBytes , img->width , img->height , img->channels , direction);
                    if (check == 0){
                        printf("Wind sucsessfuly added");
                    }
                }
                else if (input == 2){
                    int tileSize , spacing;
                    printf("Enter tile Size (10 to %d): " , img->width);
                    scanf("%d" , &tileSize);
                    printf("Enter spacing (0 to %d): " , tileSize );
                    scanf("%d", &spacing);
                    int check = tilesEffect(tmpBytes , img->width , img->height , img->channels , tileSize , spacing);
                    if (check == 0){
                        printf("tiles sucsessfuly added");
                    }
                }
                else if (input == 3){
                    int check = diffuseEffect(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("diffuse sucsessfuly added");
                    }
                }

//                else if (input == 4){
//                    int pixelSize , depth;
//                    printf("Enter pixel size: ");
//                    scanf("%d", &pixelSize);
//                    printf("Enter depth: ");
//                    scanf("%d", &depth);
//                    int check = extrudeEffect(img->bytes , img->width , img->height ,img->channels  ,pixelSize ,depth);
//                    if (check == 0){
//                        printf("diffuse sucsessfuly added");
//                    }
//                }
                else if (input == 5){
                    int check = findEdgeEffect(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("find edge added!");
                    }
                }
                else if (input == 6){
                    int direction;
                    int strength;
                    printf("Enter wind direction : (-1 ot 1)");
                    scanf("%d", &direction);
                    printf("Enter wind strength : (1 to 100)");
                    scanf("%d", &strength);
                    int check = windEffect(tmpBytes , img->width , img->height , img->channels ,strength , direction);
                    if (check == 0){
                        printf("Wind effect added!");
                    }
                }
                else if (input == 7){
                    int check=applyEmbbossFilter(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Embboss sucsessfuly added"); //stylize
                    }
                }
                else if (input == 8){
                    printf("Enter Brush Size: (1 to 10): ");
                    int brushSize;
                    scanf("%d", &brushSize);
                    int check=applyOilPainting(tmpBytes , img->width , img->height , img->channels , brushSize);
                    if (check == 0){
                        printf("OilPainting sucsessfuly added"); //stylize
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 5://cartooDrawing
                printf("Cartoon & Drawing\n1-Cartoonize\n2-Invert\n3-Pencil Sketch\n4-Posterize");
                scanf("%d", &input);
                if (input == 1){
                    int check = applyCartoonize(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Cartoonize sucsessfuly added");
                    }
                }
                else if (input == 2){
                    int check = applyInvertFilter(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Invert sucsessfuly added"); // with cartoonize
                    }
                }
                else if (input == 3){
                    int check=applyPencilSketch(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("PencilSketch sucsessfuly added"); // with cartoonize
                    }
                }
                else if (input == 4){
                    int check=applyPosterize(tmpBytes , img->width , img->height ,img->channels);
                    if (check == 0){
                        printf("Posterize sucsessfuly added");// with cartoonize
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 6://blur
                printf("Blur\n1-Gaussian Blur");
                scanf("%d", &input);
                if (input == 1){
                    int check=applyGaussianBlurFilter(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("GaussianBlur sucsessfuly added");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 7://pixelate
                printf("Pixelate:\n1-Crystalize\n2-Halftone");
                scanf("%d" , &input);
                if (input == 1){
                    int cellSize;
                    printf("Enter cell Size: (1 to 50): ");
                    scanf("%d", &cellSize);
                    int check = applyCrystalizeFilter(tmpBytes , img->width , img->height , img->channels , cellSize);
                    if (check == 0){
                        printf("Crystalize added!");
                    }
                }
                else if (input == 2){
                    int check=applyHalftone(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Halftone sucsessfuly added");
                    }
                }
                else if (input == 3){
                    int blockSize;
                    printf("Enter Block Size: ");
                    scanf("%d" , &blockSize);
                    int check = applyMosaicFilter(tmpBytes , img->width , img->height , img->channels , blockSize);
                    if (check == 0){
                        printf("Halftone sucsessfuly added");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 8://solarize
                printf("Solarize\n1-Solarize\n2-Thresholding");
                scanf("%d", &input);
                if (input == 1){
                    int check=applySolarizeFilter(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Solarize sucsessfuly added");
                    }
                }
                else if (input == 2){
                    int treshold;
                    printf("Enter Treshold : (0 to 255)");
                    scanf("%d", &treshold);
                    int check=applyThresholding(tmpBytes , img->width , img->height , img->channels ,treshold );
                    if (check == 0){
                        printf(" sucsessfuly added");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 9://borders
                printf("1-Vignette");
                scanf("%d" , &input);
                if (input == 1) {
                    int check=apply_vignette(tmpBytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("Vignette sucsessfuly added"); // with borders
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                    continue;
                }
                break;
            case 0: //exit

                return;
            default:
                printf("Invalid Input");

        }
        printf("Do you accept the effect?\n1-Yes\n2-No");
        popupImage(tmpBytes , img->width , img->height , img->channels);
        scanf("%d", &input);
        if (input == 1){
            memcpy(img->bytes, tmpBytes,  img->width * img->height * img->channels * sizeof(unsigned char));
        }
        free(tmpBytes);
    }
}

void fileHandler(){
    int input;
    img = (struct Image *) malloc(sizeof(struct Image) * imageSize);
    while (1){
        printf("Enter Input Method\n1. Local File\n2. URL\n3. Gmail");
        scanf("%d", &input);
        int check;
        switch (input){
            case 1:;
                printf("Enter source path: ");
                char* source = strInput();
                check = fileLocal(source , 1);
                if (check != 0){
                    continue;
                }
                break;
            case 2:;
                char* url = (char*) malloc(strSize);
                printf("Enter Url: ");
                scanf("%s", url);
                char* src2;
                check = download_image(url , &src2);
                printf("in user handler %s", src2);
                if (check != 0){
                    printf("download Unsuccessful");
                    continue;
                }
                check = fileLocal(src2 , 2);
                if (check != 0){
                    continue;
                }
                printf("%d %d %d", img->width , img->height , img->channels);
                free(url);
                break;
            case 3:;
                char* emailAdd = (char*) malloc(strSize);
                char* pass = (char*) malloc(strSize);
                printf("Enter your email address: ");
                scanf("%s", emailAdd);
                printf("(Now you should go google account -> secutiry -> 2-Step Verification -> App passwords "
                       "-> and now generate new ""temporary password & paste it here): ");
                scanf("%s" , pass);
                printf("Enter source path: ");
                char* destination = strInput();
                check = email(emailAdd , pass , destination);
                if (check != 0){
                    printf("receiving email Unsuccessful");
                }
                check = fileLocal(destination , 3);
                if (check != 0){
                    continue;
                }
                break;
            default:
                printf("Invalid Input!");
        }
        break;
    }

}


void userHandler(){
    welcomeMenu();

    while (1){
        // choose option
        fileHandler();

        // which Effect category
        effectHandler();

        // destination path
        saveHandler();
        if (endMenu() == 0){
            break;
        }
    }
}

