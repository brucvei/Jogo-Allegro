#include <stdio.h>
#include <allegro5/allegro.h>


int main(void){
	if (!al_init()){
        printf("Allegro nao inicializado");
        return -1;
	}

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	display = al_create_display(400, 400);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/60);

	al_install_keyboard();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	BOOL running = TRUE;

	return 0;
}

