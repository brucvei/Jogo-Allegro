#pragma once
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"

#include <vector>
#include <cmath>
#include  <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

class Game
{
public:
    Game();
    void init();
    void update();
    void render();
    void handleInput();
    void dispose();

    bool collide(float x1, float y1, float r1, float x2, float y2, float r2)
    {
        float distX = x1 - x2;
        float distY = y1 - y2;
        float dist = sqrt(distX * distX + distY * distY);

        if(dist <= r1 + r2)
        {
            return true;
        }
        return false;
    }

private:
    Background* background;
    Player player;

    std::vector<Enemy*> enemies;
    std::vector<Explosion*> explosions;

    ALLEGRO_TIMER* levelTimer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_FONT* font;
    ALLEGRO_AUDIO_STREAM* bgm;

    ALLEGRO_SAMPLE* playerHitSample;
    ALLEGRO_SAMPLE* enemyHitSample;

    ALLEGRO_SAMPLE* playerDeadSample;
    ALLEGRO_SAMPLE_ID playerDeadSampleID;

    ALLEGRO_SAMPLE* enemyDeadSample;
    ALLEGRO_SAMPLE_ID enemyDeadSampleID;

    int currentLevel;
    bool gameOver;

    ALLEGRO_KEYBOARD_STATE key_state;
};
