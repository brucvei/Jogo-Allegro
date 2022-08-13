#pragma once
#include<stdio.h>

struct background
{
    int x = 0, y = 0;
    char filename[50];
    ALLEGRO_BITMAP* backgroundImage;
};
