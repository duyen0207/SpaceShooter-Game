
#ifndef SPACE_SHIP_h
#define SPACE_SHIP_h

#include "BaseFunctions.h"
#include "BaseObject.h"
#include "Bullets.h"
#include "EnemiesShip.h"

const int SHIP_WIDTH = 80;
const int SHIP_HEIGHT = 80;

const int EARTH_WIDTH=200;
const int EARTH_HEIGHT=200;

const int step=5;



struct Spaceship : BaseObjects
{
    int x_=300;
    int y_=500;
    int v_x=0, v_y=0;
    string shape_bullet;
    int count_life;
    int collected_power;
    Uint32 coins_amount;
    vector<Bullet*> bullet_list;

    Spaceship();
    ~Spaceship();

    void die();
    void InputAction(SDL_Event &e, SDL_Renderer* &renderer);
    void move();
    //BULLET
    void after_get_power();
    void reset_bullet_shape(){shape_bullet="images//bullet.png";}
    void shoot(SDL_Renderer* &renderer);
    void destroy(const int& i_bullet);
};

#endif // SPACE_SHIP_h
