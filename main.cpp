#include "BaseFunctions.h"
#include "MySpaceship.h"
#include "EnemiesShip.h"
#include "Text.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* g_font=NULL;
Mix_Music* g_music=NULL;
Mix_Chunk* ship_die=NULL;
SDL_Event e;

int main(int argc, char* argv[]){

    initSDL(window, renderer, g_font, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

//background//
    BaseObjects g_background;
    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    int scrollingOffset=0;
    //score of player
    A_Text g_score;
    g_score.set_color(0,255,255);
    Uint32 mark=0;
    //background music
    load_mp3_sound(g_music, "sound_effect//background_music.mp3");

//characters//
    Spaceship HYPERION;
    int num_life=3;
    load_wav_sound(ship_die, "sound_effect//bum.wav");
    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);

    Enemies e_ship;
    e_ship.loadImg("images//aaa.png", renderer, E_WIDTH, E_HEIGHT);

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

        ////Play the music
        if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic( g_music, -1 );
        }
        //time
        Uint32 time_val=SDL_GetTicks()/1000;
        //Score
        string str_mark="Score: ";
        string mark_val=to_string(mark);
        str_mark+=mark_val;//connect Score with mark value -> a string

        g_score.name=str_mark;
        g_score.LoadFromRenderTexture(g_font, renderer);
        g_score.renderText(renderer, 2, 10);
    ///////////////////////////////////////////////////////////////////////
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ){
                quit=true;
            }
            HYPERION.InputAction(e, renderer);
        }
        //enemy
        if(time_val>10){
            e_ship.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            e_ship.render(renderer, e_ship.x_e, e_ship.y_e);
        }

        //Render spaceship
        HYPERION.move();
        HYPERION.render(renderer, HYPERION.x_, HYPERION.y_);
        //Shoot bullets
        HYPERION.shoot(renderer);
        //check collision between bullets and enemy
        for(int k=0; k<HYPERION.bullet_list.size(); k++){
            Bullet* b_col= HYPERION.bullet_list.at(k);
            if(b_col->blt_checkCollision(e_ship.ob_rect)){
                mark++;
                b_col->is_move=false;
                e_ship.set_position();

                HYPERION.bullet_list.erase(HYPERION.bullet_list.begin()+k);
                if(b_col!=NULL){
                    delete b_col;
                    b_col=NULL;
                }
            }
        }
        //check collision between spaceship and enemy
        if(HYPERION.spac_checkCollision(e_ship.ob_rect)){
            Mix_PlayChannel( -1, ship_die, 0 );
            cout<<endl<<endl<<"   GAME OVER!"<<endl;
            quit=true;
        }

        //present on screen
        SDL_RenderPresent(renderer);

    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

