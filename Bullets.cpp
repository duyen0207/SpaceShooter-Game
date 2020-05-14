#include "Bullets.h"

Bullet::Bullet(){
    ob_rect.x = 0;
    ob_rect.y = 0;
    ob_rect.h = 0;
    ob_rect.w = 0;
    x_b = 0;
    y_b = 0;
    is_move=false;
    type=1;
}

Bullet::~Bullet(){
    objectFree();
}


void Bullet::set_type_of_bullet(int _type_bullet){
    type=_type_bullet;
    switch(type){
        case 2:
            ob_rect.w=A1_W;
            ob_rect.h=A1_H;
            break;
        case 3:
            ob_rect.w=S_W;
            ob_rect.h=S_H;
            break;
        case 4:
            ob_rect.w=B_W;
            ob_rect.h=B_H;
            break;
        case 5:
            ob_rect.w=SS_W;
            ob_rect.h=SS_H;
            break;
        default:
            ob_rect.w=A_W;
            ob_rect.h=A_H;
            break;
    }

}

void Bullet::move_b(const int& width, const int& height, const bool direction, const int speed){
    //direction = true->move down to up, false-> up to down
    if(direction){y_b-=speed;}
    else if(!direction){y_b+=speed;}
    if(y_b<0 || y_b>height || x_b<0 || x_b>width){
        is_move=false;
    }
}

