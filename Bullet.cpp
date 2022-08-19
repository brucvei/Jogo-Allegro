#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Bullet.h"
#include "Constants.h"

Bullet::Bullet(float angle_, float x_, float y_) : angle(angle_), x(x_), y(y_)
{
    init();
}

void Bullet::init()
{
    radius = 4;
    speed = 12;

    dx = cos(angle) * speed;
    dy = sin(angle) * speed;

    alive = true;
    color = al_map_rgb_f(0.3, 0.7, 0);
}

void Bullet::update()
{
    x += dx;
    y += dy;
}

void Bullet::render()
{
    al_draw_filled_circle(x, y, radius, al_map_rgb_f(1, 0, 1));
    al_draw_circle(x, y, radius, color, 4);
}
