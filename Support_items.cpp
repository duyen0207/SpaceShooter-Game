#include "Support_items.h"

Reward::Reward(){
    ob_rect.x = 0;
    ob_rect.y = 0;
    ob_rect.w=0;
    ob_rect.h=0;
    is_move=false;
}

Reward::~Reward(){
    objectFree();
}

void Reward::simple_move(){

}
