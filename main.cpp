#include "BaseFunctions.h"
#include "BaseObject.h"
#include "MySpaceship.h"
#include "EnemiesShip.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event e;



int main(int argc, char* argv[]){

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    BaseObjects g_background;
    Spaceship HYPERION;
    Enemies e_ship;

    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);
    e_ship.loadImg("images//r.jpg", renderer, E_WIDTH, E_HEIGHT);

    int scrollingOffset=0;
    bool quit = false;
    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ){
                quit=true;
            }
            HYPERION.InputAction(e, renderer);
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
        HYPERION.move();
        HYPERION.render(renderer, HYPERION.x_, HYPERION.y_);

        //Shoot bullets
        HYPERION.shoot(renderer);

        //enemy
        e_ship.render(renderer, e_ship.x_e, e_ship.y_e);
        e_ship.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        //present on screen
        SDL_RenderPresent(renderer);

    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

