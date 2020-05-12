#include "Bullets.h"

Bullet::Bullet(){
    ob_rect.x = 0;
    ob_rect.y = 0;
    ob_rect.h = 0;
    ob_rect.w = 0;
    x_b = 0;
    y_b = 0;
    is_move=false;
}

Bullet::~Bullet(){
    objectFree();
}

void Bullet::after_get_power(){

}

void Bullet::move_b(const int& width, const int& height, const bool direction, const int speed){
    //direction = true->move down to up, false-> up to down
    if(direction){y_b-=speed;}
    else if(!direction){y_b+=speed;}
    if(y_b<0 || y_b>height || x_b<0 || x_b>width){
        is_move=false;
    }
}

