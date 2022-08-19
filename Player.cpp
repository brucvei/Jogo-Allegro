#include "Player.h"
#include "Constants.h"

#include<iostream>
#include<vector>
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
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/6);
    recoveryTimer = al_create_timer(2);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(recoveryTimer));
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

    ALLEGRO_EVENT event;
    if(al_get_next_event(event_queue, &event) && event.timer.source == recoveryTimer)
    {
        al_stop_timer(recoveryTimer);
    }

    if(firing)
    {
        if(!al_get_timer_started(timer))
        {
            al_start_timer(timer);
            fireBullet();
        }
        if(event.timer.source == timer)
        {
            fireBullet();
        }

        if(al_get_next_event(event_queue, &event))
            fireBullet();
    }
    else
    {
        al_stop_timer(timer);
    }

    for (auto& bullet : bullets)
    {
        bullet->update();
    }

    for (auto bullet = bullets.begin(); bullet !=  bullets.end(); ++bullet)
    {
        if((*bullet)->remove())
        {
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
    if(al_get_timer_started(recoveryTimer))
    {
        color = al_map_rgb_f(1, 1, 1);
    }
    else
    {
        color = al_map_rgb_f(0, 0, 1);
    }

    al_draw_filled_circle(x, y, radius, al_map_rgb_f(0, 0, 1));
    al_draw_circle(x, y, radius, al_map_rgb_f(1, 1, 1), 3);

    for (auto& bullet : bullets)
    {
        bullet->render();
    }

    // Draw lives
    for (int i = 0; i < lives; i++)
    {
        al_draw_filled_circle(30 + i * 30, 30, radius, color);
        al_draw_circle(30 + i * 30, 30, radius, color, 3);
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
    for (auto& bullet : bullets)
    {
        delete bullet;
    }

    bullets.clear();
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_timer(recoveryTimer);
}
