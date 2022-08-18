#pragma once
#include<iostream>
#include<allegro5/allegro.h>
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
    bool shooting;

    ALLEGRO_KEYBOARD_STATE key_state;

    std::vector<Bullet*> bullets;
};
