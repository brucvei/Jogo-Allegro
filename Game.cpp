#include "Game.h"

Game::Game() {}

void Game::init()
{
    background = new Background("image.jpg");
    player.init();
}

void Game::update()
{
    background->update();
    player.update();
}

void Game::render()
{
    background->render();
    player.render();
}

void Game::handleInput()
{
    player.handleInput();
}

void Game::dispose()
{
    background->dispose();
    player.dispose();
}
