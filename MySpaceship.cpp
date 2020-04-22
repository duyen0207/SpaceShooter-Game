#include "MySpaceship.h"
#include "Bullets.h"

Spaceship::Spaceship(){
    ob_rect.x=x_;
    ob_rect.y=y_;
    ob_rect.w=SHIP_WIDTH;
    ob_rect.h=SHIP_HEIGHT;
}

Spaceship::~Spaceship(){

}

void Spaceship::InputAction(SDL_Event e, SDL_Renderer* renderer){

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: v_y -= step; break;
            case SDLK_DOWN: v_y += step; break;
            case SDLK_LEFT: v_x -= step; break;
            case SDLK_RIGHT: v_x += step; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: v_y += step; break;
            case SDLK_DOWN: v_y -= step; break;
            case SDLK_LEFT: v_x += step; break;
            case SDLK_RIGHT: v_x -= step; break;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button==SDL_BUTTON_LEFT){
            Bullet* a_bullet = new Bullet();
            a_bullet->loadImg("images//bullet.png", renderer, NORMAL_WIDTH, NORMAL_HEIGHT);
            a_bullet->x_b=x_+SHIP_WIDTH*0.35; a_bullet->y_b=y_;
            a_bullet->is_move=true;
            bullet_list.push_back(a_bullet);
        }
    }
}

void Spaceship::move(){
    x_+=v_x;
    y_+=v_y;
    if(x_<0) x_+=step;
    if(x_>SCREEN_WIDTH-SHIP_WIDTH) x_-=step;
    if(y_<0) y_+=step;
    if(y_>SCREEN_HEIGHT-SHIP_HEIGHT) y_-=step;
}

void Spaceship::shoot(SDL_Renderer* renderer){
    for(int i=0; i<bullet_list.size(); i++){
            Bullet* ptr_b= bullet_list.at(i);
            if(ptr_b!=NULL){
                if(ptr_b->is_move){
                    ptr_b->move_b(SCREEN_WIDTH, SCREEN_HEIGHT, true);
                    ptr_b->render(renderer, ptr_b->x_b, ptr_b->y_b);
                }else{
                    bullet_list.erase(bullet_list.begin()+i);
                    if(ptr_b!=NULL){
                        delete ptr_b;
                        ptr_b=NULL;
                    }
                }
            }
    }
}

