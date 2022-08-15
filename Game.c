#include <stdio.h>

extern void initBackground();
extern void updateBackground();
extern void renderBackground();
extern void disposeBackground();

//#include "Constants.h"

void initGame()
{
    initBackground("image.jpg");
};

void updateGame()
{

};

void renderGame()
{

};

void handleInputGame()
{

};

void disposeGame()
{
    disposeBackground();
};
