#include<stdio.h>
#include <stdbool.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

struct player
{
    float x, y, radius;                  // Posicao e tamanho
    float dx, dy, velociade;             // Vetor
    bool esquerda, direita, cima, baixo, atirando; // Movimento
};

ALLEGRO_KEYBOARD_STATE key_state;
ALLEGRO_EVENT_QUEUE* event_queue_2;
ALLEGRO_TIMER* timer_2;

struct player Player;

extern void initBullet();
extern void updateBullet();
extern void renderBullet();
extern float removeBullet();

void initPlayer()
{
    Player.x = 30;
    Player.y = 400 / 2;
    Player.radius = 10;

    Player.dx = 0;
    Player.dy = 0;
    Player.velociade = 8;

    Player.esquerda = Player.direita = Player.cima = Player.baixo = Player.atirando = false;

    event_queue_2 = al_create_event_queue();
    timer_2 = al_create_timer(1.0/5);

    al_register_event_source(event_queue_2, al_get_timer_event_source(timer_2));
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
    }
    else
    {
        Player.dx = 0;
    }

    if(Player.cima)
    {
        Player.dy = - Player.velociade;
    }
    else if (Player.baixo)
    {
        Player.dy = Player.velociade;
    }
    else
    {
        Player.dy = 0;
    }

    Player.x += Player.dx;
    Player.y += Player.dy;

    if(Player.x < Player.radius) Player.x = Player.radius;
    if(Player.y < Player.radius) Player.y = Player.radius;

    if(Player.x + Player.radius > 800) Player.x = 800 - Player.radius;
    if(Player.y + Player.radius > 400) Player.y = 400 - Player.radius;

    if(Player.atirando){
            printf("qi");
        if(al_get_timer_started(timer_2)){
            al_start_timer(timer_2);
            initBullet(0, Player.x, Player.y);
        }
        ALLEGRO_EVENT event_2;
        if(al_get_next_event(event_queue_2, &event_2)){
           initBullet(0, Player.x, Player.y);
        }
    } else {
        al_stop_timer(timer_2);
    }

    updateBullet();

    removeBullet();
};

void handleInputPlayer()
{
    al_get_keyboard_state(&key_state);

    Player.esquerda = al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    Player.direita  = al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    Player.cima     = al_key_down(&key_state, ALLEGRO_KEY_UP);
    Player.baixo    = al_key_down(&key_state, ALLEGRO_KEY_DOWN);
    Player.atirando = al_key_down(&key_state, ALLEGRO_KEY_SPACE);
};

void renderPlayer()
{
    al_draw_filled_circle(Player.x, Player.y, Player.radius, al_map_rgb_f(0, 0, 1));
    al_draw_circle(Player.x, Player.y, Player.radius, al_map_rgb_f(1, 1, 1), 3);

    renderBullet();
};

void disposePlayer()
{
    removeBullet();

    al_destroy_event_queue(event_queue_2);
    al_destroy_timer(timer_2);
};
