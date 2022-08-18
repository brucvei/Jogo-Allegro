#include<stdio.h>
#include<math.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

struct enemy
{
    float x, y, angle, radius;
    float dx, dy, velociade;
    int star, lives;
    bool isOnScreen;
};

struct enemy Enemy;
ALLEGRO_COLOR color;

float getXEnemy()
{
    return Enemy.x;
}

float getYEnemy()
{
    return Enemy.y;
}

float getRadiusEnemy()
{
    return Enemy.radius;
}

float toRadians(float angle)
{
    return angle * 3.1415 / 180;
}

void hit()
{
    Enemy.lives --;
}
bool isDead ()
{
    return Enemy.lives <= 0;
}

void initEnemy(int star)
{
    switch(star)
    {
    case 1:
        color = al_map_rgb_f(1, 0, 0);
        Enemy.velociade = 4;
        Enemy.lives = 1;
        break;
    case 2:
        color = al_map_rgb_f(0, 1, 0);
        Enemy.velociade = 6;
        Enemy.lives = 2;
        break;
    case 3:
        color = al_map_rgb_f(0, 0, 1);
        Enemy.velociade = 6;
        Enemy.lives = 3;
        break;
    case 4:
        color = al_map_rgb_f(1, 0, 1);
        Enemy.velociade = 6;
        Enemy.lives = 5;
        break;
    case 5:
        color = al_map_rgb_f(0, 1, 1);
        Enemy.velociade = 8;
        Enemy.lives = 6;
        break;
    }

    Enemy.radius = 10;
    Enemy.x = 800 - Enemy.radius;
    Enemy.y = 400 / 2;
    Enemy.angle = (90 + rand() % 181);
    Enemy.dx = -(abs(cos(toRadians(Enemy.angle)) * Enemy.velociade));
    Enemy.dy = sin(toRadians(Enemy.angle)) * Enemy.velociade;
    Enemy.isOnScreen = false;
};

void updateEnemy()
{
    Enemy.x += Enemy.dx;
    Enemy.y += Enemy.dy;

    if (Enemy.x < 800) Enemy.isOnScreen = true;

    //Bounds checking
    if (Enemy.isOnScreen)
    {
        if (Enemy.x < Enemy.radius) Enemy.dx = -Enemy.dx;
        if (Enemy.y < Enemy.radius) Enemy.dy = -Enemy.dy;
        if (Enemy.x + Enemy.radius > 800) Enemy.dx = -Enemy.dx;
        if (Enemy.y + Enemy.radius > 800) Enemy.dy = -Enemy.dy;
    }
};

void renderEnemy()
{
    al_draw_filled_circle(Enemy.x, Enemy.y, Enemy.radius, color);
};

void disposeEnemy()
{

};
