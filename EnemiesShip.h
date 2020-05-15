#ifndef ENEMIES_h
#define ENEMIES_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"

const int E_WIDTH = 70;
const int E_HEIGHT = 50;

const int BOSS_WIDTH=200;
const int BOSS_HEIGHT=150;

const int speed_e=3;
const int num_enemy=10;

const int TIME_BOSS_APPEAR=150;
const int SPEED_BULLET=4;
const int SPEED_BOSS=3;
const int num_bullet_of_boss=4;
const int sum_life_of_enemy_S=30;


struct Enemies : BaseObjects{
    int x_e;
    int y_e;
    bool moveHorizontal;
    Bullet e_bullet;

    Enemies();
    ~Enemies();

    void free_enemies();

    void set_position();
    void HandleMove(int &life_boss, const int& x_max, const int& y_max, const int speed_e);
    void shoot(SDL_Renderer* renderer, const int speed);
    void set_bullet_position(int pos_x=E_WIDTH/2, const int &E_H=E_HEIGHT){e_bullet.x_b=x_e+pos_x; e_bullet.y_b=y_e+E_H; e_bullet.is_move=true;}

    void Boss_move(const int x_limit, const int y_limit, int speed_boss);
    void Boss_die(int &num_life, const int type_bullet);
};

#endif // ENEMIES_h

