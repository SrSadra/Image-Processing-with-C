#include <SFML/Graphics.h>

#define paths "Data//test.png"

int popupImage(unsigned char* imageBinary , int width , int height , int channels){
    int result = stbi_write_png(paths, width, height, channels, imageBinary, width * channels);
    if (result == 0) {
        return 1;
    }
    const char* imagePath = paths;

    sfImage* image = sfImage_createFromFile(imagePath);
    if (!image) {
        // Handle image loading error
        return 1;
    }

    const sfUint8* imageData = sfImage_getPixelsPtr(image);

    sfTexture* texture = sfTexture_create(width, height);
    sfTexture_updateFromPixels(texture, imageData, width, height, 0, 0);

    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    sfVideoMode mode = {width, height, 8 * channels};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Image Pop-up", sfClose, NULL);
//    sfRenderWindow_setSize(window, (sfVector2u){width, height});
    sfRenderWindow_clear(window, sfBlack);

    sfRenderWindow_drawSprite(window, sprite, NULL);

    sfRenderWindow_display(window);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
    }

    sfRenderWindow_destroy(window);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfImage_destroy(image);

    return 0;
}