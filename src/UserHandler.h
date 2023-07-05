#include <stdio.h>
#include "File.h"
#include "Image.h"
#include "Effects\\Noise.h"
#include "Effects\\Color.h"
#include "Effects\\Redeye.h"
#include "Effects\\Stylize.h"
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
                    // costum 3 - hue adjustment
                else if (input == 3){
                    float heuInp , saturationInp , brightnessInp;
                    printf("Enter hue in range -180 to 180: ");
                    scanf("%f" , &heuInp);
                    printf("Enter saturation in range -100 to 100: ");
                    scanf("%f" , &saturationInp);
                    printf("Enter hue in range -100 to 100: ");
                    scanf("%f" , &brightnessInp);
                    int check = applyHslAdjustment(img->bytes , img->width , img->height , img->channels , heuInp , saturationInp , brightnessInp);
                    if (check == 0){
                        printf("Hsl applied");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                }
                break;
            case 2: //add noise
                scanf("%d", &input);
                if (input == 1){
                    int percent;
                    printf("Enter Amount of noise (0 , 400): ");
                    scanf("%d", &percent);
                    addNoise(img->bytes , img->width , img->height , percent , img->channels);
                    printf("noise sucsessfuly added");
                }

                break;
            case 3:
                scanf("%d", &input);
                if (input == 1){
                    int check = removeRedEye(img->bytes , img->width , img->height , img->channels );
                    if (check == 0){// modify check before graphic
                        printf("Red Eye reduced");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                }
                break;
            case 4:
                scanf("%d" , &input);
                if (input == 1){
                    int direction , strength;
                    printf("Enter Wind direction (90 for upward , 180 for right to legt...): ");
                    scanf("%d" , &direction);
                    printf("Enter Wind strength:");
                    scanf("%d", &strength);
                    int check = windEffect(img->bytes , img->width , img->height , img->channels , direction , strength);
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
                    int check = tilesEffect(img->bytes , img->width , img->height ,img->channels , tileSize , spacing);
                    if (check == 0){
                        printf("tiles sucsessfuly added");
                    }
                }
                else if (input == 3){
                    int check = diffuseEffect(img->bytes , img->width , img->height ,img->channels);
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
                    int check = findEdgeEffect(img->bytes , img->width , img->height , img->channels);
                    if (check == 0){
                        printf("find edge added!");
                    }
                }
                else {
                    printf("Invalid Filter/Input!");
                }
            case 0: //exit

                return;
                break;
            default:
                printf("Invalid Input");
        }
    }

}

void fileHandler(int input){
    img = (struct Image *) malloc(sizeof(struct Image) * imageSize);

    switch (input){
        case 1:;
            char* path = (char*) malloc(strSize);
            scanf("%s", path);
            printf("%s", path);
            if (setFormat(path , img) == -1) {
                printf("Invalid format!");
            }
            img->bytes = readfile( &(img->width) , &(img->height) , &(img->channels) , path , img->format );
            printf("%d", img->channels);
            img->type = 1;
            img->path = path;
            free(path);
            break;
        case 2:;
            char* url = (char*) malloc(strSize);
            char* dest = (char*) malloc(strSize);
            printf("Enter Url: ");
            scanf("%s", url);
            printf("Enter destination to save: ");
            scanf("%s" , dest);
            img->bytes = download_image(url, dest,&(img->width) , &(img->height), &(img->channels));
            img->type = 1;
            img->path = url;
            free(url);
            break;
        case 3:;
            char* url2 = (char*) malloc(strSize);
//            char* dest = (char*) malloc(strSize);
            printf("Enter Url: ");
            scanf("%s", url2);
//            printf("Enter destination to save: ");
//            scanf("%s" , dest);
            img->bytes = downloadImage(url2, &(img->width) , &(img->height), &(img->channels));
            printf("%d %d %d", img->width , img->height , img->channels);
            img->type = 1;
            img->path = url2;
            free(url2);
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
//        // which Effect category
        effectHandler();

        // destination path
        saveHandler();
        break;// temporary


    }
}

// struct Image * imageHandler(){
//     struct Image img;
// }
