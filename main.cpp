#include "BaseFunctions.h"
#include "BaseObject.h"
#include "MySpaceship.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event e;



int main(int argc, char* argv[]){

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    BaseObjects g_background;
    Spaceship HYPERION;

    while(true){

        g_background.loadImg("images//galaxy2.jpg", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        g_background.render(renderer, 0, 0);
        HYPERION.loadObject("images//spaceship.png", renderer);
        HYPERION.show(renderer, HYPERION.x_, HYPERION.y_);
        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);

        SDL_Delay(10);

        if ( SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE:break;
        		case SDLK_LEFT:HYPERION.moveLeft(); break;
        		case SDLK_RIGHT:HYPERION.moveRight(); break;
            		case SDLK_DOWN:HYPERION.moveDown(); break;
            		case SDLK_UP:HYPERION.moveUp(); break;
        		default: break;
			}
        }
        g_background.~BaseObjects();
        HYPERION.~BaseObjects();
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

