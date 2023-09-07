#include <stdio.h>



struct Image {
    unsigned char* bytes;
    char * path;
    char * format;
    int type;
    int width;
    int height;
    int channels;

};


void setPath(char * path , struct Image* img){
    img->path = path;
}


void setType(int type , struct Image* img){
    img->type = type;
}

int setFormat(char* path , char ** imgFormat){
    printf("\n%s\n", path);
    char* format = strrchr(path , '.');
    format = format + 1;
    printf("--%s\n", format);
    if (!strcmp(format , "png") || !strcmp(format , "jpg") || !strcmp(format , "jpeg") || !strcmp(format , "bm")){
        *imgFormat = format;
        return 1;
    }
    else {
        return -1;
    }
}


unsigned char* copyImage(struct Image* srcImg){
    unsigned char* desImg = (unsigned char*) malloc( srcImg->width * srcImg->height * srcImg->channels * sizeof(unsigned char));
    memcpy(desImg, srcImg->bytes,  srcImg->width * srcImg->height * srcImg->channels * sizeof(unsigned char));
    return desImg;
}