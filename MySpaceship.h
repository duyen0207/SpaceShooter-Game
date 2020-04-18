
#ifndef SPACE_SHIP_h
#define SPACE_SHIP_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"
#include <vector>

const int SHIP_WIDTH = 80;
const int SHIP_HEIGHT = 80;
const int step=15;

struct Spaceship: public BaseObjects
{
    int x_=300;
    int y_=500;

    Bullet bullet_ship;

    Spaceship();
    ~Spaceship();

    void pressKeyToMove(SDL_Event e);
    void HandleBullet(SDL_Renderer* des);

    void moveLeft(){ x_-=step; if(x_<0) x_+=step;}
    void moveRight(){ x_+=step; if(x_>SCREEN_WIDTH-SHIP_WIDTH) x_-=step;}
    void moveUp(){ y_-=step; if(y_<0) y_+=step;}
    void moveDown(){ y_+=step; if(y_>SCREEN_HEIGHT-SHIP_HEIGHT) y_-=step;}
};

#endif // SPACE_SHIP_h
