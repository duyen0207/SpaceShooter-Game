
#ifndef SPACE_SHIP_h
#define SPACE_SHIP_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int SHIP_WIDTH = 80;
const int SHIP_HEIGHT = 80;

struct Spaceship: public BaseObjects
{
    int x_=300;
    int y_=200;

    Spaceship();
    ~Spaceship();

    void loadObject(string path, SDL_Renderer* renderer);
    void show(SDL_Renderer* des, int& _x, int& _y);

    void pressKeyToMove(SDL_Event e);

    void moveLeft(){ x_-=5; if(x_<0) x_+=5;}
    void moveRight(){ x_+=5; if(x_>SCREEN_WIDTH-SHIP_WIDTH) x_-=5;}
    void moveUp(){ y_-=5; if(y_<0) y_+=5;}
    void moveDown(){ y_+=5; if(y_>SCREEN_HEIGHT-SHIP_HEIGHT) y_-=5;}
};

#endif // SPACE_SHIP_h
