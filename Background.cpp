#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Background.h"
#include "Constants.h"

Background::Background(std::string filename)
{
    backgroundImage = al_load_bitmap(filename.c_str());
    if(!backgroundImage)
    {
        std::cout << "Nao foi possivel carregar imagem " << filename << std::endl;
    }
//    al_draw_bitmap(backgroundImage,0,0,0);
    y = 0;
    x = 0;
}

void Background::update()
{
    x -= 2;

    if(x < - GAME_WIDTH) x = 0;
}

void Background::render()
{
    al_draw_scaled_bitmap(backgroundImage, 0, 0, al_get_bitmap_width(backgroundImage), al_get_bitmap_height(backgroundImage), x, y, GAME_WIDTH, GAME_HEIGTH, 0);
    al_draw_scaled_bitmap(backgroundImage, 0, 0, al_get_bitmap_width(backgroundImage), al_get_bitmap_height(backgroundImage), x + GAME_WIDTH, y, GAME_WIDTH, GAME_HEIGTH, 0);
}

void Background::dispose()
{
    al_destroy_bitmap(backgroundImage);
}
