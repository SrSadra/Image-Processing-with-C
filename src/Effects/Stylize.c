int mynewFilter(unsigned char* image, int width, int height , int channels, int direction);
int tilesEffect(unsigned char* image, int width, int height , int channels, int tileSize, int spacing);
int diffuseEffect(unsigned char* image, int width, int height , int channels);
int extrudeEffect(unsigned char* image, int width, int height, int channels,int blockSize ,int depth);
int findEdgeEffect(unsigned char* image, int width, int height, int channels);
int windEffect(unsigned char* image, int width, int height,int channels ,float windStrength, float windDirection);
int applyEmbbossFilter(unsigned char* image, int width, int height, int channels);//shi
int applyOilPainting(unsigned char* image, int width, int height, int channels ,int brushSize);
