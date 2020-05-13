#include "Support_items.h"

Reward::Reward(){
    ob_rect.x = 0;
    ob_rect.y = 0;
    ob_rect.w=0;
    ob_rect.h=0;
    speed_r=3;
    bool move_cross=false;
}

Reward::~Reward(){
    objectFree();
}

void Reward::simple_move(const int p_x){
    ob_rect.y+=speed_r;
    if(move_cross){ob_rect.x+=speed_r;}
    if(ob_rect.y>SCREEN_HEIGHT || ob_rect.x>SCREEN_WIDTH){
        set_position_r(p_x);
    }
}
