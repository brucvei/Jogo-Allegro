#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//#include "Constants.h"

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

extern void initGame();
extern void updateGame();
extern void renderGame();
extern void handleInputGame();
extern void disposeGame();

#include "Constants.h"

void update()
{
    updateGame();
};

void render()
{
    //al_clear_to_color(al_map_rgb_f(1, 0, 1));

    renderGame();

    al_flip_display();
};

void handleInput()
{
    handleInputGame();
};

void dispose()
{
    disposeGame();

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
};

int main(void)
{
    if (!al_init())
    {
        printf("Allegro nao inicializado");
        return -1;
    }

    display = al_create_display(GAME_WIDTH, GAME_HEIGTH);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_install_keyboard();
    al_init_image_addon();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    bool running = true;
    bool redraw = true;

    initGame();

    al_start_timer(timer);
    while(running)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            handleInput();
            update();
            redraw = true;
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            render();
        }
    }

    dispose();

    return 0;
}
