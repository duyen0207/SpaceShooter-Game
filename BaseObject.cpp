#include "BaseObject.h"

BaseObjects:: BaseObjects(){
    object = NULL;
    ob_rect.x=0;
    ob_rect.y=0;
    ob_rect.w=0;
    ob_rect.h=0;
}

BaseObjects::~BaseObjects(){
    objectFree();
}

void BaseObjects::objectFree(){
    if(object!=NULL){
        SDL_DestroyTexture(object);
        object=NULL;
        ob_rect.w=0;
        ob_rect.h=0;
    }
}

void BaseObjects::loadImg(string path, SDL_Renderer* &screen, const int WIDTH, const int HEIGHT){
    SDL_Surface* newSurface =IMG_Load(path.c_str());
    if(newSurface != NULL){
        SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, RED, GREEN, BLUE));
        object = SDL_CreateTextureFromSurface(screen, newSurface);
        if(object!=NULL){
            ob_rect.w=WIDTH;   // save size of character.
            ob_rect.h=HEIGHT;
        }else if(object==NULL){cout<<"Can't find the path of the image."<<endl;}
        SDL_FreeSurface(newSurface);
    }
}

void BaseObjects::render(SDL_Renderer* &des, int _x, int _y){
    ob_rect.x=_x;
    ob_rect.y=_y;
    SDL_RenderCopy(des, object, NULL, &ob_rect);
}

bool BaseObjects::checkCollision(const SDL_Rect& other_rect){
    int left_this=ob_rect.x;
    int right_this=ob_rect.x+ob_rect.w;
    int top_this=ob_rect.y;
    int bottom_this=ob_rect.y+ob_rect.h;

    int left_other= other_rect.x+10;
    int right_other= other_rect.x+ other_rect.w-10;
    int top_other= other_rect.y+other_rect.h/3;
    int bottom_other= other_rect.y+other_rect.h*0.67;

    if( bottom_this < top_other )
    {
        return false;
    }

    if( top_this > bottom_other )
    {
        return false;
    }

    if( right_this < left_other )
    {
        return false;
    }

    if( left_this > right_other )
    {
        return false;
    }

    return true;

}
