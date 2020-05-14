#include "EnemiesShip.h"

Enemies::Enemies(){
    ob_rect.x = SCREEN_WIDTH/2;
    ob_rect.y = -E_HEIGHT;
    ob_rect.w=E_WIDTH;
    ob_rect.h=E_HEIGHT;
    x_e = 0;
    y_e = -E_HEIGHT;
    moveHorizontal=false;
}

Enemies::~Enemies(){
    objectFree();
}

void Enemies::set_position(){
    if(moveHorizontal){
        y_e=rand()%((SCREEN_HEIGHT-E_WIDTH)/2); x_e=-rand()%SCREEN_WIDTH;
    }
    else {y_e=-rand()%(SCREEN_HEIGHT); x_e=rand()%(SCREEN_WIDTH-E_WIDTH);}
}

void Enemies::HandleMove(const int& x_max, const int& y_max, const int speed_e){
    if(moveHorizontal){
        x_e+=speed_e;
    }
    else y_e+=speed_e;
    if(y_e>SCREEN_HEIGHT || x_e>SCREEN_WIDTH){
        set_position();
    }
}

void Enemies::shoot(SDL_Renderer* renderer, const int speed){
    if(!e_bullet.is_move) {
        e_bullet.x_b=x_e+E_WIDTH/2;
        e_bullet.y_b=y_e+E_HEIGHT;
        e_bullet.is_move=true;
    }
    e_bullet.move_b(SCREEN_WIDTH, SCREEN_HEIGHT, false, speed);
    e_bullet.render(renderer, e_bullet.x_b, e_bullet.y_b);
}

void Enemies::HandleInputAction(SDL_Event &e){

}

void Enemies::special_move(const int x_limit, const int y_limit, int speed_boss){

}

