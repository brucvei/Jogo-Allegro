#include<stdio.h>
#include<math.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

struct bullet
{
    float x, y, angle, radius;
    float dx, dy, velociade;
};

struct bullet Bullet;

float getXBullet()
{
    return Bullet.x;
}

float getYBullet()
{
    return Bullet.y;
}

float getRadiusBullet()
{
    return Bullet.radius;
}

void initBullet(float angle, float x, float y)
{
    printf("initBullet");
    Bullet.radius = 4;
    Bullet.velociade = 20;
    Bullet.dx = cos(angle) * Bullet.velociade;
    Bullet.dy = sin(angle) * Bullet.velociade;
};

void updateBullet()
{
    printf("updateBullet");
    Bullet.x += Bullet.dx;
    Bullet.y += Bullet.dy;
};

void renderBullet()
{
    printf("renderBullet");
    al_draw_filled_circle(Bullet.x, Bullet.y, Bullet.radius, al_map_rgb_f(1, 1, 1));
    al_draw_circle(Bullet.x, Bullet.y, Bullet.radius, al_map_rgb_f(0.3, 0.7,0), 3);
};

float removeBullet()
{
    printf("removeBullet");
    return Bullet.x >= al_get_display_width(al_get_current_display()) || Bullet.y >= al_get_display_height(al_get_current_display()) || Bullet.x < 0 || Bullet.y < 0;
}
