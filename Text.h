#ifndef TEXT_h
#define TEXT_h

#include "BaseFunctions.h"

struct A_Text{
    string content;
    SDL_Texture* texture;
    SDL_Color text_color;
    int width;
    int height;

    A_Text();
    ~A_Text();

    void LoadFromRenderTexture(TTF_Font* &font, SDL_Renderer* &screen);
    void set_color(Uint8 red, Uint8 green, Uint8 blue);
    void renderText( SDL_Renderer* &renderer, int x, int y,
                         SDL_Rect* clip=NULL, double angle=0.0,
                         SDL_Point* center=NULL, SDL_RendererFlip flip= SDL_FLIP_NONE );
};

#endif // TEXT_h
