#include "Explosion.h"]
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Explosion::Explosion(float x_, float y_, float radius_, ALLEGRO_COLOR color_) : x(x_), y(y_), radius(radius_), color(color_) {
    explosionTime = al_get_time();
    explosionTimeDiff = 0.5;
    stopExplosion = false;
}

void Explosion::update(){
    radius += 0.5;

    if(al_get_time() - explosionTime >= explosionTimeDiff){
        stopExplosion = true;
    }
}

void Explosion::render(){
    al_draw_circle(x, y, radius, color, 2);
}

bool Explosion::remove(){
    return stopExplosion;
}

void Explosion::dispose(){

}
