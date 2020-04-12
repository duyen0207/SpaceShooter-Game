#include "MySpaceship.h"

Spaceship::Spaceship(){
    ob_rect.x=x_;
    ob_rect.y=y_;
    ob_rect.w=SHIP_WIDTH;
    ob_rect.h=SHIP_HEIGHT;

}

Spaceship::~Spaceship(){

}

void Spaceship::loadObject(string path, SDL_Renderer* screen){
    BaseObjects::loadImg(path, screen, SHIP_WIDTH, SHIP_HEIGHT);
}

void Spaceship::show(SDL_Renderer* des, int& _x, int& _y){
    BaseObjects::render(des, _x, _y);
}

void Spaceship::pressKeyToMove(SDL_Event e){
    ob_rect.x=x_;
    ob_rect.y=y_;
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:break;
            case SDLK_LEFT:     moveLeft(); break;
            case SDLK_RIGHT:    moveRight(); break;
            case SDLK_DOWN:     moveDown(); break;
            case SDLK_UP:       moveUp(); break;
            default: break;
        }
    }
}
