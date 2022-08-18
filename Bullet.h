#pragma once
#include<iostream>
#include<allegro5/allegro.h>

class Bullet
{
public:
    Bullet(float angle, float x, float y);
    void init();
    void update();
    void render();

    float toRadians(float angle){
        return angle * 3.1415 / 180;
    }

private:
    float x;
    float y;
    float radius;

    float speed;
    float radius;
    float dx;
    float dy;

};
