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

void BaseObjects::loadImg(string path, SDL_Renderer* screen, const int WIDTH, const int HEIGHT){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* newSurface =IMG_Load(path.c_str());
    if(newSurface != NULL){
        SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, RED, GREEN, BLUE));
        newTexture = SDL_CreateTextureFromSurface(screen, newSurface);
        if(newTexture!=NULL){
            ob_rect.w=WIDTH;   // save size of character.
            ob_rect.h=HEIGHT;
        }else if(newTexture==NULL){cout<<"Can't find the path of the image."<<endl;}
        SDL_FreeSurface(newSurface);
    }
    object=newTexture;
}

void BaseObjects::render(SDL_Renderer* des, int _x, int _y){
    ob_rect.x=_x;
    ob_rect.y=_y;
    SDL_Rect newRect ={ob_rect.x, ob_rect.y, ob_rect.w, ob_rect.h};
    SDL_RenderCopy(des, object, NULL, &newRect);
}

