#include "EnemiesShip.h"

Enemies::Enemies(){
    ob_rect.x = SCREEN_WIDTH/2;
    ob_rect.y = -E_HEIGHT;
    ob_rect.w=E_WIDTH;
    ob_rect.h=E_HEIGHT;
    x_e = 0;
    y_e = -E_HEIGHT;
}

Enemies::~Enemies(){

}

void Enemies::HandleMove(const int& x_max, const int& y_max){
    y_e+=step_e;
    if(y_e>SCREEN_HEIGHT){
        y_e=-E_HEIGHT;
        x_e=rand()%(SCREEN_WIDTH-E_WIDTH);
    }
}


void Enemies::HandleInputAction(SDL_Event e){

}

