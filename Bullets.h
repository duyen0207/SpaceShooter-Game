#ifndef BULLET_h
#define BULLET_h

#include "BaseFunctions.h"
#include "BaseObject.h"

const int NORMAL_WIDTH = 20;
const int NORMAL_HEIGHT = 30;

const int step_b=5;

struct Bullet : public BaseObjects
{
    int x_b;
    int y_b;

    Bullet();
    ~Bullet();

    void after_get_power();

    void move_b(const int& width, const int& height, const bool direction);
};


#endif // BULLET_h
