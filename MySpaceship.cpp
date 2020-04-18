#include "MySpaceship.h"
#include "Bullets.h"

Spaceship::Spaceship(){
    ob_rect.x=x_;
    ob_rect.y=y_;
    ob_rect.w=SHIP_WIDTH;
    ob_rect.h=SHIP_HEIGHT;
    bullet_ship.x_b=x_+SHIP_WIDTH/3+3;
    bullet_ship.y_b=y_;
}

Spaceship::~Spaceship(){

}

void Spaceship::pressKeyToMove(SDL_Event e){

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

void Spaceship::HandleBullet(SDL_Renderer* des){
    bullet_ship.loadImg("images//bullet.png", des, NORMAL_WIDTH, NORMAL_HEIGHT);
    bullet_ship.render(des, bullet_ship.x_b, bullet_ship.y_b);
    bullet_ship.move_b(SCREEN_WIDTH, SCREEN_HEIGHT, true);
}
