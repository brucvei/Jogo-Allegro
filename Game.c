#include <stdio.h>
#include <math.h>
#include <stdbool.h>

extern void initBackground();
extern void updateBackground();
extern void renderBackground();
extern void disposeBackground();

extern void initPlayer();
extern void updatePlayer();
extern void renderPlayer();
extern void handleInputPlayer();
extern void disposePlayer();

extern float getXPlayer();
extern float getYPlayer();
extern float getRadiusPlayer();

extern float getXBullet();
extern float getYBullet();
extern float getRadiusBullet();
extern float removeBullet();

extern float getXEnemy();
extern float getYEnemy();
extern float getRadiusEnemy();

extern void initEnemy();
extern void updateEnemy();
extern void renderEnemy();
extern void disposeEnemy();

bool collide(float x1, float y1, float r1, float x2, float y2, float r2)
{
    float distX = x1 - x2;
    float distY = y1 - y2;
    float dist = sqrt(distX * distX + distY * distY);

    if(dist <= r1 + r2)
    {
        return true;
    }
    return false;
}

void initGame()
{
    initBackground("image.jpg");
    initPlayer();

    for(int i = 0; i < 4; i++)
    {
        initEnemy(1);
        initEnemy(2);
    }
};

void updateGame()
{
    updatePlayer();

    float bx, by, br;
    bx = getXBullet();
    by = getYBullet();
    br = getRadiusBullet();

    float ex, ey, er;
    ex = getXEnemy();
    ey = getYEnemy();
    er = getRadiusEnemy();

    float px, py, pr;
    px = getXPlayer();
    py = getYPlayer();
    pr = getRadiusPlayer();

    if (collide(bx, by, br, ex, ey, er))
    {
        removeBullet();
    }

    if (collide(px, py, pr, ex, ey, er))
    {
        removeBullet();
    }
};

void renderGame()
{
    initBackground("image.jpg");
    renderPlayer();
    renderEnemy();
};

void handleInputGame()
{
    //initBackground("image.jpg");
    handleInputPlayer();
};

void disposeGame()
{
    disposeBackground();
    disposePlayer();
    disposeEnemy();
};
