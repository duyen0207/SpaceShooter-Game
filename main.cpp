#include "BaseFunctions.h"
#include "MySpaceship.h"
#include "EnemiesShip.h"
#include "Text.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* g_font=NULL;
Mix_Music* g_music=NULL;
SDL_Event e;

int main(int argc, char* argv[]){

    initSDL(window, renderer, g_font, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

//background//
    BaseObjects g_background;
    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    int scrollingOffset=0;

    A_Text g_time;
    g_time.set_color(0,255,255);
    //background music
    load_mp3_sound(g_music, "sound_effect//background_music.mp3");

//characters//
    Spaceship HYPERION;
    Enemies e_ship;

    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);
    e_ship.loadImg("images//r.jpg", renderer, E_WIDTH, E_HEIGHT);
//play game//
    bool quit = false;
    while(!quit)
    {
        //Clear screen
        SDL_RenderClear( renderer );
    //GAME BACKGROUND//
        //Scroll background
        scrollingOffset+=2;
        if( scrollingOffset > SCREEN_HEIGHT ){
            scrollingOffset = 0;
        }
        //Render background
        g_background.render(renderer, 0, scrollingOffset - SCREEN_HEIGHT);
        g_background.render(renderer, 0, scrollingOffset);

        //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
        {   //Play the music
            Mix_PlayMusic( g_music, -1 );
        }

        //time
        string time="Time: ";
        Uint32 time_val=SDL_GetTicks()/1000;

        string gtime=to_string(time_val);
        time+=gtime;

        g_time.name=time;
        g_time.LoadFromRenderTexture(g_font, renderer);
        g_time.renderText(renderer, 2, 10);
    ///////////////////////////////////////////////////////////////////////
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ){
                quit=true;
            }
            HYPERION.InputAction(e, renderer);
        }


        //enemy
        if(time_val>30){
            e_ship.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            e_ship.render(renderer, e_ship.x_e, e_ship.y_e);
        }

        //Render spaceship
        HYPERION.move();
        HYPERION.render(renderer, HYPERION.x_, HYPERION.y_);
        //Shoot bullets
        HYPERION.shoot(renderer);

        //check collision between spaceship and enemy
        if(HYPERION.checkCollision(e_ship.ob_rect)){
            cout<<endl<<endl<<"   GAME OVER!"<<endl;
            quit=true;
        }
        //check collision between bullets and enemy


        //present on screen
        SDL_RenderPresent(renderer);

    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

