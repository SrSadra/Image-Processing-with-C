#include <stdio.h>



struct Image {
    unsigned char * bytes;
    char * path;
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