#ifndef SUPPORT_ITEMS_h
#define SUPPORT_ITEMS_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int LIFE_WEIGHT=70;
const int LIFE_HEIGHT=30;

const int POWER_WEIGHT=70;
const int POWER_HEIGHT=30;

const int DIAMOND_WEIGHT=50;
const int DIAMOND_HEIGHT=50;

struct Reward : BaseObjects{
    bool is_move;

    Reward();
    ~Reward();

    void simple_move();
};

#endif // SUPPORT_ITEMS_h
