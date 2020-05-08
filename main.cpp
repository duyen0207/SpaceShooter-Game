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
//main elements in game
BaseObjects g_background;
Spaceship HYPERION;
Enemies e_ship[num_enemy];
//additional elements
bool quit = false;
int scrollingOffset=0;
A_Text g_score;
Uint32 mark=0;
int num_life=1;

void load_game_elements();
void enemis_appear(Uint32 &time); //manage time for appearance of types of enemies

int main(int argc, char* argv[]){

    initSDL(window, renderer, g_font, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    load_game_elements();

//play game//
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
        if( Mix_PlayingMusic() == 0 ){ Mix_PlayMusic( g_music, -1 );}
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
        enemis_appear(time_val);
        //Render spaceship
        HYPERION.move();
        HYPERION.render(renderer, HYPERION.x_, HYPERION.y_);
        HYPERION.shoot(renderer);
        //check collision between spaceship, bullets and enemy
        for(int e_c=0; e_c<num_enemy; ++e_c){
            //bullet of spaceship and enemies
            for(int k=0; k<HYPERION.bullet_list.size(); k++){
                Bullet* b_col= HYPERION.bullet_list.at(k);
                if(b_col->blt_checkCollision(e_ship[e_c].ob_rect)){
                    mark++;
                    b_col->is_move=false;
                    e_ship[e_c].set_position();

                    HYPERION.bullet_list.erase(HYPERION.bullet_list.begin()+k);
                    if(b_col!=NULL){
                        delete b_col;
                        b_col=NULL;
                    }
                }
            }
            //spaceship and enemies/bullet of enemy
            if(HYPERION.spac_checkCollision(e_ship[e_c].ob_rect) || HYPERION.spac_checkCollision(e_ship[e_c].e_bullet.ob_rect)){
                Mix_PlayChannel( -1, ship_die, 0 );
                if(num_life<1){
                    cout<<endl<<endl<<"   GAME OVER!"<<endl<<endl<<"Your score is: "<<mark<<endl;
                    quit=true;
                }
            }
        }
        //present on screen
        SDL_RenderPresent(renderer);
    }
    waitUntilKeyPressed();

    quitSDL(window, renderer);
    return 0;
}

void load_game_elements(){
    //background and sound
    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    load_mp3_sound(g_music, "sound_effect//background_music.mp3");
    load_wav_sound(ship_die, "sound_effect//bum.wav");

    g_score.set_color(0,255,255);
    //spaceship
    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);
    //enemies
    for(int e=0; e<num_enemy; e++){
        e_ship[e].loadImg("images//aaa.png", renderer, E_WIDTH, E_HEIGHT);
        e_ship[e].e_bullet.loadImg("images//e_bullet.png", renderer, B_W, B_H);
    }
}

void enemis_appear(Uint32 &time){
    if(time>5){
        for(int ee=0; ee<num_enemy; ee++){
            e_ship[ee].HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, speed_e);
            e_ship[ee].render(renderer, e_ship[ee].x_e, e_ship[ee].y_e);
            e_ship[ee].shoot(renderer, speed2);
        }
    }
}
