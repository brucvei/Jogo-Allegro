#include "Game.h"
#include "Constants.h"

Game::Game() {}

void Game::init()
{
    background = new Background("image.jpg");
    player.init();

    currentLevel = 1;
    levelTimer = al_create_timer(5);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(levelTimer));
    al_start_timer(levelTimer);

    font = al_create_builtin_font();
    bgm = al_load_audio_stream("music.ogg", 2, 2048);
    al_set_audio_stream_playmode(bgm, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(bgm, true);

    al_attach_audio_stream_to_mixer(bgm, al_get_default_mixer());

}

void Game::update()
{
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
                enemy->hit();
                if(player.isDead())
                {
                    //Game over
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
                        //Game over
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
            enemies.erase(enemy);
            enemy--;
        }
    }

    if(enemies.size() == 0)
    {
        al_start_timer(levelTimer);
    }
}

void Game::render()
{
    if(al_get_timer_started(levelTimer))
    {
        al_draw_textf(font, al_map_rgb_f(1, 1, 1), GAME_WIDTH / 2, GAME_HEIGTH / 2, ALLEGRO_ALIGN_CENTER, "Nivel %i", currentLevel);
    }

    background->render();
    player.render();

    for (auto& enemy : enemies)
    {
        enemy->render();
    }
}

void Game::handleInput()
{
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

    enemies.clear();
    al_destroy_timer(levelTimer);
    al_destroy_font(font);
    al_destroy_audio_stream(bgm);
}
