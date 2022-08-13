#include<stdio.h>
#include<allegro5/allegro.h>

#include "Background.h"
#include "Constants.h"

struct background Background;

void initBackground(char filename[50])
{
    Background.backgroundImage = al_load_bitmap(filename);
    if(!Background.backgroundImage)
    {
        printf("Nao foi possivel carregar imagem");
    }

}

void updateBackground()
{
    Background.x -= 2;
    if(Background.x < -GAME_WIDTH) x = 0;
};

void renderBackground()
{
    al_draw_scaled_bitmap(Background.backgroundImage, 0, 0, al_get_bitmap_width(Background.backgroundImage), al_get_bitmap_height(Background.backgroundImage), Background.x, Background.y, GAME_WIDTH, GAME_HEIGTH, 0);
    ]
    al_draw_scaled_bitmap(Background.backgroundImage, 0, 0, al_get_bitmap_width(Background.backgroundImage), al_get_bitmap_height(Background.backgroundImage), GAME_WIDTH + Background.x, Background.y, GAME_WIDTH, GAME_HEIGTH, 0);
};

void disposeBackground()
{
    al_destroy_bitmap(Background.backgroundImage);
};
