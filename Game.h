#pragma once
#include "Background.h"
#include "Player.h"

class Game
{
public:
    Game();
    void init();
    void update();
    void render();
    void handleInput();
    void dispose();

private:
    Background* background;
    Player player;

};
