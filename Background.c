#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>

struct background
{
    int x, y;
    char filename[50];
};

ALLEGRO_BITMAP* backgroundImage;

struct background Background;

void initBackground(char filename[50])
{
    backgroundImage = al_load_bitmap(filename);
    if(!backgroundImage)
    {
        printf("Nao foi possivel carregar imagem");
    }
    al_draw_bitmap(backgroundImage,0,0,0);
}

void disposeBackground()
{
    al_destroy_bitmap(backgroundImage);
};
