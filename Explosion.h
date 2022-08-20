#pragma once
#include <allegro5/allegro.h>

class Explosion {
public:
    Explosion(float x, float y, float radius, ALLEGRO_COLOR color);
    void update();
    void render();
    bool remove();
    void dispose();

private:
    float x;
    float y;
    float radius;
    float explosionTime;
    float explosionTimeDiff;
    bool stopExplosion;

    ALLEGRO_COLOR color;
};
