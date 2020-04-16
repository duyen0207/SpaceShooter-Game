#include "Bullets.h"

Bullet::Bullet(){
    ob_rect.x = 0;
    ob_rect.y = 0;
    ob_rect.h = 0;
    ob_rect.w = 0;
    x_b = 0;
    y_b = 0;

}

Bullet::~Bullet(){

}

void Bullet::after_get_power(){

}

void Bullet::move_b(const int& width, const int& height, const bool direction){
    if(direction){y_b-=step_b;}
    else if(!direction){y_b+=step_b;}
    if(y_b<0 || y_b>height || x_b<0 || x_b>width){
        objectFree();
    }
}

