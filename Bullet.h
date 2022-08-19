#pragma once
#include<iostream>
#include<allegro5/allegro.h>

class Bullet
{
public:
    Bullet(float angle_, float x_, float y_);
    void init();
    void update();
    void render();

    float toRadians(float angle)
    {
        return angle * 3.1415 / 180;
    }

    void setColor(ALLEGRO_COLOR color_)
    {
        color = color_;
    }

    void setSpeed(int val)
    {
        speed = val;
    }

    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getRadius()
    {
        return radius;
    }

    bool isAlive()
    {
        return alive;
    }
    void kill()
    {
        alive = false;
    }


    bool remove()
    {
        return x >= al_get_display_width(al_get_current_display()) || y >= al_get_display_height(al_get_current_display()) || x < 0 || y < 0 || !alive;
    }

private:
    float x;
    float y;
    float radius;

    float speed;
    float angle;
    float dx;
    float dy;
    bool alive;

    ALLEGRO_COLOR color;
};
