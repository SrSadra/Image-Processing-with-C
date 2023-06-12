struct Image {
    unsigned char * bytes;
    char * path;
    int type;
    int width;
    int height;
    int channels;
};


void setPath(char * path , struct Image* img);

void setType(int type , struct Image* img);

