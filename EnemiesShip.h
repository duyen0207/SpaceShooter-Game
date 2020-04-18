#ifndef ENEMIES_h
#define ENEMIES_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int E_WIDTH = 90;
const int E_HEIGHT = 70;
const int step_e=4;

struct Enemies : public BaseObjects{
    int x_e;
    int y_e;

    Enemies();
    ~Enemies();

    void HandleMove(const int& x_max, const int& y_max);
    void HandleInputAction(SDL_Event e);

};

#endif // ENEMIES_h

