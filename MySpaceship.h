
#ifndef SPACE_SHIP_h
#define SPACE_SHIP_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"
#include <vector>

const int SHIP_WIDTH = 80;
const int SHIP_HEIGHT = 80;

struct Spaceship: public BaseObjects
{
    int x_=300;
    int y_=500;
    int v_x=0, v_y=0;
    const int step=5;

    vector<Bullet*> bullet_list;

    Spaceship();
    ~Spaceship();

    void InputAction(SDL_Event e, SDL_Renderer* renderer);
    void move();
    //BULLET
    void shoot(SDL_Renderer* renderer);
};

#endif // SPACE_SHIP_h
