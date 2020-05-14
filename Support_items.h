#ifndef SUPPORT_ITEMS_h
#define SUPPORT_ITEMS_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int LIFE_WEIGHT=70;
const int LIFE_HEIGHT=30;

const int POWER_WEIGHT=70;
const int POWER_HEIGHT=30;

const int COIN_WEIGHT=30;
const int COIN_HEIGHT=30;

const int num_coins=10;

struct Reward : BaseObjects{
    int speed_r;
    bool move_cross;

    Reward();
    ~Reward();

    void set_speed(const int sp){speed_r=sp;}
    void set_position_r(int position_x, int position_y=-(rand()%SCREEN_HEIGHT)){ob_rect.x=position_x; ob_rect.y=position_y;}
    void simple_move(const int p_x);
};

#endif // SUPPORT_ITEMS_h
