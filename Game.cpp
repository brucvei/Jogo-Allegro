#include "Game.h"
#include "Constants.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

Game::Game() {}

void Game::init()
{
    background = new Background("image.jpg");
    player.init();

    currentLevel = 1;
    levelTimer   = al_create_timer(5);
    event_queue  = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(levelTimer));
    al_start_timer(levelTimer);

    font = al_create_builtin_font();
    bgm  = al_load_audio_stream("music.ogg", 2, 2048);
    al_set_audio_stream_playmode(bgm, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(bgm, true);

    al_attach_audio_stream_to_mixer(bgm, al_get_default_mixer());

    playerHitSample  = al_load_sample("playerHit.wav");
    enemyHitSample   = al_load_sample("enemyHit.wav");
    playerDeadSample = al_load_sample("playerDead.wav");
    enemyDeadSample  = al_load_sample("enemyDead.wav");

    gameOver = false;
}

void Game::update()
{
    if(gameOver)
    {
        return;
    }

    for (auto& explosion : explosions)
    {
        explosion->update();
    }

    player.update();

    if(al_get_timer_started(levelTimer))
    {
        ALLEGRO_EVENT event;
        if(al_get_next_event(event_queue, &event))
        {
            al_stop_timer(levelTimer);
            if(enemies.size() == 0)
            {
                switch (currentLevel)
                {
                case 1:
                    for(int i = 0; i < 4; i++)
                    {
                        enemies.emplace_back(new Enemy(1));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    break;
                case 2:
                    for(int i = 0; i < 8; i++)
                    {
                        enemies.emplace_back(new Enemy(1));
                    }
                    for(int i = 0; i < 4; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    break;
                case 3:
                    for(int i = 0; i < 4; i++)
                    {
                        enemies.emplace_back(new Enemy(1));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    for(int i = 0; i < 4; i++)
                    {
                        enemies.emplace_back(new Enemy(3));
                    }
                    break;
                case 4:
                    for(int i = 0; i < 4; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(3));
                    }
                    break;
                case 5:
                    for(int i = 0; i < 6; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    break;
                case 6:
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(1));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(3));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(4));
                    }
                    break;
                case 7:
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(2));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(3));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(4));
                    }
                    for(int i = 0; i < 2; i++)
                    {
                        enemies.emplace_back(new Enemy(5));
                    }
                    break;
                }
            }
            currentLevel++;
        }
        return;
    }

    background->update();

    for (auto& enemy : enemies)
    {
        enemy->update(player.getX(), player.getY());
    }

    for (auto& bullet : player.getBullets())
    {
        auto bx = bullet->getX();
        auto by = bullet->getY();
        auto br = bullet->getRadius();

        for(auto& enemy : enemies)
        {
            auto ex = enemy->getX();
            auto ey = enemy->getY();
            auto er = enemy->getRadius();

            if(!enemy->isRecovering())
            {
                if (collide(bx, by, br, ex, ey, er))
                {
                    //Decrease the enemy's life
                    enemy->hit();
                    al_play_sample(enemy->isDead() ? enemyDeadSample : enemyHitSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &enemyDeadSampleID);
                    //Remove the bullet
                    bullet->kill();
                }
            }

        }
    }

    if(!player.isRecovering())
    {
        for(auto& enemy : enemies)
        {
            auto ex = enemy->getX();
            auto ey = enemy->getY();
            auto er = enemy->getRadius();

            auto px = player.getX();
            auto py = player.getY();
            auto pr = player.getRadius();

            if(collide(px, py, pr, ex, ey, er))
            {
                player.hit();
                al_play_sample(player.isDead() ? playerDeadSample : playerHitSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &playerDeadSampleID);
                enemy->hit();
                if(player.isDead())
                {
                    gameOver = true;
                }
            }
        }
    }

    if(!player.isRecovering())
    {
        for(auto& enemy : enemies)
        {
            for(auto& bullet : enemy->getBullets())
            {
                auto bx = bullet->getX();
                auto by = bullet->getY();
                auto br = bullet->getRadius();

                auto px = player.getX();
                auto py = player.getY();
                auto pr = player.getRadius();

                if(collide(px, py, pr, bx, by, br))
                {
                    player.hit();
                    bullet->kill();
                    if(player.isDead())
                    {
                        gameOver = true;
                    }
                }
            }
        }
    }
    //Remove dead objects
    for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
    {
        if ((*enemy)->isDead())
        {
            explosions.emplace_back(new Explosion((*enemy)->getX(), (*enemy)->getY(), (*enemy)->getRadius(), (*enemy)->getColor()));
            enemies.erase(enemy);
            enemy--;
        }
    }

    for(auto explosion = explosions.begin(); explosion != explosions.end(); explosion++)
    {
        if ((*explosion)->remove())
        {
            explosions.erase(explosion);
            explosion--;
        }
    }

    if(enemies.size() == 0)
    {
        al_start_timer(levelTimer);
    }
}

void Game::render()
{
    if(gameOver)
    {
        al_draw_textf(font, al_map_rgb_f(1, 1, 1), GAME_WIDTH / 2, GAME_HEIGTH / 2, ALLEGRO_ALIGN_CENTER, "%s", "Game Over! Press Z to restart");
        return;
    }

    if(al_get_timer_started(levelTimer))
    {
        al_draw_textf(font, al_map_rgb_f(1, 1, 1), GAME_WIDTH / 2, GAME_HEIGTH / 2, ALLEGRO_ALIGN_CENTER, "Nivel %i", currentLevel);
    }

    background->render();
    player.render();

    for (auto& explosion : explosions){
        explosion->render();
    }

    for (auto& enemy : enemies)
    {
        enemy->render();
    }
}

void Game::handleInput()
{
    if(gameOver)
    {
        al_get_keyboard_state(&key_state);
        if(al_key_down(&key_state, ALLEGRO_KEY_Z)){
            gameOver = false;
            player.dispose();
            player.init();
            currentLevel = 1;
            for(auto& e : enemies){
                e->dispose();
                delete e;
            }
            enemies.clear();
            al_flush_event_queue(event_queue);
        }

        return;
    }

    player.handleInput();
}

void Game::dispose()
{
    background->dispose();
    player.dispose();

    for (auto& enemy : enemies)
    {
        enemy->dispose();
        delete enemy;
    }

    for (auto& explosion : explosions)
    {
        explosion->dispose();
        delete explosion;
    }

    explosions.clear();
    enemies.clear();
    al_destroy_timer(levelTimer);
    al_destroy_font(font);
    al_destroy_audio_stream(bgm);

    al_destroy_sample(playerDeadSample);
    al_destroy_sample(playerHitSample);
    al_destroy_sample(enemyDeadSample);
    al_destroy_sample(enemyHitSample);
}
