#include <stdio.h>

extern void initBackground();
extern void updateBackground();
extern void renderBackground();
extern void disposeBackground();

void initGame()
{
    initBackground("src/stars.jpg");
};

void updateGame()
{
    updateBackground();
};

void renderGame()
{
    renderBackground();
};

void handleInputGame()
{

};

void disposeGame()
{
    disposeBackground();
};
