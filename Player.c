#include<stdio.h>
#include <stdbool.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

struct player
{
    float x, y, radius;                  // Posicao e tamanho
    float dx, dy, velociade;             // Vetor
    bool esquerda, direita, cima, baixo; // Movimento
};

ALLEGRO_KEYBOARD_STATE key_state;

struct player Player;

void initPlayer()
{
    Player.x = 30;
    Player.y = 400 / 2;
    Player.radius = 10;

    Player.dx = 0;
    Player.dy = 0;
    Player.velociade = 8;

    Player.esquerda = Player.direita = Player.cima = Player.baixo = false;
};

void updatePlayer()
{
    if(Player.esquerda)
    {
        Player.dx = - Player.velociade;
    }
    else if (Player.direita)
    {
        Player.dx = Player.velociade;
    } else {
        Player.dx = 0;
    }

    if(Player.cima)
    {
        Player.dy = - Player.velociade;
    }
    else if (Player.baixo)
    {
        Player.dy = Player.velociade;
    } else {
        Player.dy = 0;
    }

    Player.x += Player.dx;
    Player.y += Player.dy;

    if(Player.x < Player.radius) Player.x = Player.radius;
    if(Player.y < Player.radius) Player.y = Player.radius;
    if(Player.x + Player.radius > 800) Player.x = 800 - Player.radius;
    if(Player.y + Player.radius > 400) Player.y = 400 - Player.radius;
};

void handleInputPlayer()
{
    al_get_keyboard_state(&key_state);

    Player.esquerda = al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    Player.direita = al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    Player.cima = al_key_down(&key_state, ALLEGRO_KEY_UP);
    Player.baixo = al_key_down(&key_state, ALLEGRO_KEY_DOWN);
};

void renderPlayer()
{
    al_draw_filled_circle(Player.x, Player.y, Player.radius, al_map_rgb_f(0, 0, 1));
    al_draw_circle(Player.x, Player.y, Player.radius, al_map_rgb_f(1, 1, 1), 3);
};

void disposePlayer()
{

};
