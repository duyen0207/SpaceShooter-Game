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

    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    HYPERION.loadObject("images//spaceship.png", renderer);

    int scrollingOffset=0;
    bool quit = false;
    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ){
                quit=true;
            }
            HYPERION.pressKeyToMove(e);
        }
        //Scroll background
        scrollingOffset++;
        if( scrollingOffset > SCREEN_HEIGHT ){
            scrollingOffset = 0;
        }
            //Clear screen
        SDL_RenderClear( renderer );

        //Render background
        g_background.render(renderer, 0, scrollingOffset - SCREEN_HEIGHT);

        g_background.render(renderer, 0, scrollingOffset);
        //Render spaceship
        HYPERION.show(renderer, HYPERION.x_, HYPERION.y_);

        HYPERION.HandleBullet(renderer);

        SDL_RenderPresent(renderer);

    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

