#pragma once
#include<iostream>
#include<allegro5/allegro.h>
#include<vector>

#include "Bullet.h"
class Enemy
{
public:
    Enemy(int star_);
    void init();
    void update(float playerX, float playerY);
    void render();
    void dispose();

    float toRadians(float angle)
    {
        return angle * 3.1415 / 180;
    }

    void hit()
    {
        lives --;
        al_start_timer(recoveryTimer);
    }
    bool isDead ()
    {
        return lives <= 0;
    }

    bool isRecovering()
    {
        return al_get_timer_started(recoveryTimer);
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

    std::vector<Bullet*> getBullets()
    {
        return bullets;
    }

private:
    int star;
    float x;
    float y;
    float radius;

    float speed;
    float dx;
    float dy;
    float angle;

    int lives;

    ALLEGRO_COLOR color;
    ALLEGRO_COLOR recoveyColor;
    bool isOnScreen;

    std::vector<Bullet*> bullets;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* recoveryTimer;
};
