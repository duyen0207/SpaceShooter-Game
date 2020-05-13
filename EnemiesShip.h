#ifndef ENEMIES_h
#define ENEMIES_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"

const int E_WIDTH = 70;
const int E_HEIGHT = 50;
const int speed_e=3;
const int num_enemy=5;


struct Enemies : BaseObjects{
    int x_e;
    int y_e;
    bool moveHorizontal;
    Bullet e_bullet;

    Enemies();
    ~Enemies();

    void free_enemies();

    void set_position();
    void HandleMove(const int& x_max, const int& y_max, const int speed_e);
    void shoot(SDL_Renderer* renderer, const int speed);
    void set_bullet_position(){e_bullet.x_b=x_e+E_WIDTH/2; e_bullet.y_b=y_e+E_HEIGHT; e_bullet.is_move=true;}
    void HandleInputAction(SDL_Event &e);

};

#endif // ENEMIES_h

