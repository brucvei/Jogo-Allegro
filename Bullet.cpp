#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Bullet.h"
#include "Constants.h"

Bullet::Bullet(float angle, float x, float y) : angle(angle_), x(x_), y(y_)
{
    init();
}

void Bullet::init()
{
    radius = 4;
    speed = 20;

    dx = cos(angle) * speed;
    dy = sin(angle) * speed;

    //Bullet.alive = true;
}

void Bullet::update()
{
    x += dx;
    y += dy;
}

void Bullet::render()
{
    al_draw_filled_circle(x, y, radius, al_map_rgb_f(1, 1, 1));
    al_draw_circle(x, y, radius, al_map_rgb_f(0.3, 0.7,0), 4);
}

