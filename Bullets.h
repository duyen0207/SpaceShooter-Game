#ifndef BULLET_h
#define BULLET_h

#include "BaseFunctions.h"
#include "BaseObject.h"

//level of bullet
const int B_W=20;
const int B_H=20;

const int A_W = 20;
const int A_H = 30;

const int S_W = 50;
const int S_H = 50;

const int SS_W =70;
const int SS_H =70;

//speed of bullet
const int speed1=6;
const int speed2=4;

struct Bullet : BaseObjects
{
    int x_b;
    int y_b;
    bool is_move;

    Bullet();
    ~Bullet();

    void after_get_power();
    void move_b(const int& width, const int& height, const bool direction, const int speed);

};


#endif // BULLET_h
