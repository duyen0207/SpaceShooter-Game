#ifndef ENEMIES_h
#define ENEMIES_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"

const int E_WIDTH = 90;
const int E_HEIGHT = 70;
const int step_e=5;

struct Enemies : BaseObjects{
    int x_e;
    int y_e;
    Bullet e_bullet;

    Enemies();
    ~Enemies();

    void HandleMove(const int& x_max, const int& y_max);
    void shoot(SDL_Renderer* renderer, const int& x_max, const int& y_max);
    void HandleInputAction(SDL_Event &e);

};

#endif // ENEMIES_h

