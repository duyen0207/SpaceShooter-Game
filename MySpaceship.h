
#ifndef SPACE_SHIP_h
#define SPACE_SHIP_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int SHIP_WIDTH = 64;
const int SHIP_HEIGHT = 64;

struct Spaceship: public BaseObjects
{
    int x_=300;
    int y_=200;

    Spaceship();
    ~Spaceship();

    void loadObject(string path, SDL_Renderer* renderer);
    void show(SDL_Renderer* des, int& _x, int& _y);

    void pressKeyToMove(SDL_Event e);

    void moveLeft(){ x_-=5;}
    void moveRight(){ x_+=5;}
    void moveUp(){ y_-=5;}
    void moveDown(){ y_+=5;}

    bool inside(int minX, int minY, int maxX, int maxY){
        return (minX<=x_ && minY<=y_ && x_+SHIP_WIDTH<=maxX && y_+SHIP_HEIGHT<=maxY);
    }
};

#endif // SPACE_SHIP_h
