#pragma once
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_audio.h>
#include<vector>

#include "Bullet.h"
class Player
{
public:
    Player();
    void init();
    void update();
    void render();
    void handleInput();
    void dispose();

    void fireBullet();

    std::vector<Bullet*> getBullets()
    {
        return bullets;
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

    void hit()
    {
        lives--;
        al_start_timer(recoveryTimer);
    }
    bool isDead()
    {
        return lives <= 0;
    }
    bool isRecovering()
    {
        return al_get_timer_started(recoveryTimer);
    }


private:
    float x;
    float y;
    float radius;
    float speed;

    float dx;
    float dy;

    bool left;
    bool right;
    bool up;
    bool down;
    bool firing;

    int lives;

    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* recoveryTimer;
    ALLEGRO_COLOR color;
    ALLEGRO_SAMPLE* shootSample;
    ALLEGRO_SAMPLE_ID shootID;

    std::vector<Bullet*> bullets;
};
