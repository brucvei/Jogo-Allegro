#include "Player.h"
#include "Constants.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Player::Player() {}

void Player::init()
{
    x = 30;
    y = GAME_HEIGTH / 2;
    dx = 0;
    dy = 0;
    speed = 8;
    radius = 10;

    left = right = up = down = firing = false;
}

void Player::update()
{
    if(left)
    {
        dx = - speed;
    }
    else if (right)
    {
        dx = speed;
    }
    else
    {
        dx = 0;
    }

    if(up)
    {
        dy = - speed;
    }
    else if (down)
    {
        dy = speed;
    }
    else
    {
        dy = 0;
    }

    x += dx;
    y += dy;

    if(x < radius) x = radius;
    if(y < radius) y = radius;

    if(x + radius > GAME_WIDTH) x = GAME_WIDTH - radius;
    if(y + radius > GAME_HEIGTH) y = GAME_HEIGTH - radius;

    if(firing)
    {
        fireBullet();
    }

    for (auto& bullet : bullets){
        bullet->update();
    }

    for (auto bullet = bullets.begin(); bullet !=  bullets.end(); ++bullet){
        if((*bullet)->remove()){
            bullets.erase(bullet);
            bullet--;
        }
    }
}

void Player::fireBullet()
{
    bullets.emplace_back(new Bullet(0, x, y));
}

void Player::render()
{
    al_draw_filled_circle(x, y, radius, al_map_rgb_f(0, 0, 1));
    al_draw_circle(x, y, radius, al_map_rgb_f(1, 1, 1), 3);

    for (auto& bullet : bullets){
        bullet->render();
    }
}

void Player::handleInput()
{
    al_get_keyboard_state(&key_state);

    left   = al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    right  = al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    up     = al_key_down(&key_state, ALLEGRO_KEY_UP);
    down   = al_key_down(&key_state, ALLEGRO_KEY_DOWN);
    firing = al_key_down(&key_state, ALLEGRO_KEY_SPACE);
}

void Player::dispose()
{
    for (auto& bullet : bullets){
        delete bullet;
    }

    bullets.clear();
}
