#ifndef BULLET_h
#define BULLET_h

#include "BaseFunctions.h"
#include "BaseObject.h"

//level of bullet
    //ENEMY
    //type 4
    const int B_W=20;
    const int B_H=20;
    //type 5
    const int SS_W =70;
    const int SS_H =70;
    //SPACESHIP
    //type 1
    const int A_W = 20;
    const int A_H = 30;
    //type 2
    const int A1_W = 60;
    const int A1_H = 35;
    //type 3
    const int S_W = 100;
    const int S_H = 40;


//speed of bullet
const int speed1=6;
const int speed2=4;

struct Bullet : BaseObjects
{
    int x_b;
    int y_b;
    bool is_move;
    int type;

    Bullet();
    ~Bullet();

    void set_type_of_bullet(int _type_bullet=1);
    void move_b(const int& width, const int& height, const bool direction, const int speed);
    void move_bullet_of_boss(int enemy_x, int enemy_y, int speed, int direction=false);
    void set_position_(int x_pp, int y_pp){x_b=x_pp; y_b=y_pp; is_move=true;}
};


#endif // BULLET_h
