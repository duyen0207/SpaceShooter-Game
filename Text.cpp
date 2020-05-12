#include "Text.h"

A_Text::A_Text(){
    text_color.r=255;
    text_color.g=255;
    text_color.b=255;
    texture=NULL;
}

A_Text::~A_Text(){
    if(texture!=NULL){
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}

void A_Text::LoadFromRenderTexture(TTF_Font* &font, SDL_Renderer* &screen){
    SDL_Surface* print_text = TTF_RenderText_Solid(font, content.c_str(), text_color);
    if(print_text!=NULL){
        texture=SDL_CreateTextureFromSurface(screen, print_text);
        width=print_text->w;
        height=print_text->h;
        SDL_FreeSurface(print_text);
    } else {
        cout<<"Error font."<<endl;
    }
}

void A_Text::set_color(Uint8 red, Uint8 green, Uint8 blue){
    text_color.r=red;
    text_color.g=green;
    text_color.b=blue;
}

void A_Text::renderText( SDL_Renderer* &renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}
