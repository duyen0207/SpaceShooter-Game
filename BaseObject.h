#ifndef Base_Object_h
#define Base_Object_h

#include "BaseFunctions.h"

//this class is used for apply images of background and characters on screen

struct BaseObjects {

    SDL_Texture* object; //save image of character
    SDL_Rect ob_rect;    //save size and location of character

    BaseObjects();
    ~BaseObjects();

    void loadImg(string path, SDL_Renderer* &screen, const int WIDTH, const int HEIGHT); //save image to a texture
    void render(SDL_Renderer* &des, int _x, int _y);  //apply texture to screen with its location
    bool checkCollision(const SDL_Rect& other_rect);
    void objectFree(); //free pointer
};
#endif // Base_Object_h
