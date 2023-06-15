#include <stdio.h>



struct Image {
    unsigned char * bytes;
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

int setFormat(char* path , struct Image* img){
    printf("\n%s\n", path);
    char* format = strrchr(path , '.');
    printf("%s\n", format);
    if (!strcmp(format , ".png")){
        img->format = "png";
        return 1;
    }
    else if (!strcmp(format , ".jpg")){
        img->format = "jpg";
        return 1;
    }
    else {
        return -1;
    }
}