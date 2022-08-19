#include "Enemy.h"
#include "Constants.h"
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Enemy :: Enemy(int star_) : star(star_)
{
    init();
}

void Enemy::init()
{
    switch(star)
    {
    case 1:
        color = al_map_rgb_f(1, 0, 0);
        speed = 2;
        lives = 1;
        break;
    case 2:
        color = al_map_rgb_f(0, 1, 0);
        speed = 4;
        lives = 2;
        break;
    case 3:
        color = al_map_rgb_f(0, 0, 1);
        speed = 5;
        lives = 3;
        break;
    case 4:
        color = al_map_rgb_f(1, 0, 1);
        speed = 6;
        lives = 5;
        break;
    case 5:
        color = al_map_rgb_f(0, 1, 1);
        speed = 8;
        lives = 6;
        break;
    }
    radius = 10;
    x = GAME_WIDTH - radius;
    y = GAME_HEIGTH / 2;
    angle = (90 + rand() % 181);
    dx = -(fabs(cos(toRadians(angle)) * speed));
    dy = sin(toRadians(angle)) * speed;
    isOnScreen = false;

    event_queue = al_create_event_queue();
    recoveryTimer = al_create_timer(0.5);
    al_register_event_source(event_queue, al_get_timer_event_source(recoveryTimer));
}

void Enemy::update(float playerX, float playerY)
{
    x += dx;
    y += dy;

    if (x < GAME_WIDTH) isOnScreen = true;

    //Bounds checking
    if (isOnScreen)
    {
        if (x < radius) dx = -dx;
        if (y < radius) dy = -dy;
        if (x + radius > GAME_WIDTH) dx = -dx;
        if (y + radius > GAME_WIDTH) dy = -dy;
    }

    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event))
    {
        al_stop_timer(recoveryTimer);
    }

    if (star > 2)
    {
        int prob = rand() % 500;

        if(prob == 1)
        {
            float angle = atan2(playerY - y, playerX - x);

            Bullet* bullet = new Bullet(angle, x, y);
            bullet->setColor(al_map_rgb_f(1, 0, 0));
            bullet->setSpeed(8);
            bullets.push_back(bullet);
        }
    }

    for(auto& bullet : bullets)
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

void Enemy::render()
{
    if (al_get_timer_started(recoveryTimer))
    {
        recoveyColor = al_map_rgb_f(1, 1, 1);
    }

    al_draw_filled_circle(x, y, radius, al_get_timer_started(recoveryTimer) ? recoveyColor : color);

    for(auto& bullet : bullets)
    {
        bullet->render();
    }
}

void Enemy::dispose()
{
    for (auto& bullet : bullets)
    {
        delete bullet;
    }
    bullets.clear();

    al_destroy_event_queue(event_queue);
    al_destroy_timer(recoveryTimer);
}
