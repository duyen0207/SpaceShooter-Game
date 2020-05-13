#include "BaseFunctions.h"
#include "MySpaceship.h"
#include "EnemiesShip.h"
#include "Support_items.h"
#include "Text.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* g_font=NULL;
Mix_Music* g_music=NULL;
Mix_Chunk* ship_die=NULL;
SDL_Event e;
    //main elements in game
    BaseObjects g_background;
    BaseObjects g_menu;
    BaseObjects g_menu_end;
    BaseObjects text_in_the_end;
            //CHARACTERS AND ITEMS
            Spaceship HYPERION;
            Enemies e_ship[num_enemy];
            Reward diamonds[num_diamonds];
            Reward Life;
            Reward Power[num_power];
                //additional elements
                bool win=false;
                bool quit = false;
                int scrollingOffset=0;
                A_Text g_score; Uint32 mark=0;
                BaseObjects NUM_DIAMONDS; A_Text amount_diamonds; Uint32 amount_d=0;
                int count_life=1;

bool Menu_Game();
void load_game_elements();
void object_appear(Uint32 &time); //manage time for appearance of types of objects


void Play_Game();
void End_Game();


void close();//to free all elements in game

//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){

    initSDL(window, renderer, g_font, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    Play_Game();

    close();
    quitSDL(window, renderer);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////


bool Menu_Game(){
    A_Text to_play;
    to_play.set_color(255, 128, 128);
    to_play.content="Play Game";

    bool is_continue=true;
    while(is_continue){
        SDL_RenderClear( renderer );
        g_menu.render(renderer, 0, 0);
        to_play.LoadFromRenderTexture(g_font, renderer);
        to_play.renderText(renderer, 150, 513);
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&e)!=0){
            if( e.type == SDL_QUIT ){
                is_continue=false;
                return false;
            }
            else if(e.type==SDL_MOUSEMOTION || e.type==SDL_MOUSEBUTTONDOWN){
                if(e.motion.x>=130 && e.motion.x<=400 && e.motion.y>=500 && e.motion.y<=550){
                    to_play.set_color(0, 255, 0);
                    if(e.button.button==SDL_BUTTON_LEFT){
                        return true;
                        is_continue=false;
                    }
                }
                else to_play.set_color(255, 128, 128);
            }else break;
        }
    }
}

void load_game_elements(){
    //menu
    g_menu.loadImg("images//menu.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_menu_end.loadImg("images//menu_end.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //background and sound
    g_background.loadImg("images//galaxy.png", renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    load_mp3_sound(g_music, "sound_effect//background_music.mp3");
    load_wav_sound(ship_die, "sound_effect//bum.wav");
    //SCORE
    g_score.set_color(0,255,255);
    NUM_DIAMONDS.loadImg("images//tinh_thach.png", renderer, DIAMOND_WEIGHT, DIAMOND_HEIGHT);
    amount_diamonds.set_color(0, 255, 255);
        //REWARD
        Life.loadImg("images//support_life.png", renderer, LIFE_WEIGHT, LIFE_HEIGHT);
        for(int p=0; p<num_power; p++){
            Power[p].loadImg("images//power.png", renderer, POWER_WEIGHT, POWER_HEIGHT);
        }
        for(int r=0; r<num_diamonds; r++){
            diamonds[r].loadImg("images//tinh_thach.png", renderer, DIAMOND_WEIGHT, DIAMOND_HEIGHT);
            diamonds[r].set_position_r(SCREEN_WIDTH/2, -(r+1)*(DIAMOND_HEIGHT+5));
        }

    //spaceship
    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);
    //enemies
    for(int e=0; e<num_enemy; e++){
        e_ship[e].loadImg("images//aaa.png", renderer, E_WIDTH, E_HEIGHT);
        e_ship[e].set_position();
        e_ship[e].e_bullet.loadImg("images//e_bullet.png", renderer, B_W, B_H);
    }
}

void object_appear(Uint32 &time){

    if(time>5){
        for(int ee=0; ee<num_enemy; ee++){
            e_ship[ee].HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, speed_e);
            e_ship[ee].render(renderer, e_ship[ee].x_e, e_ship[ee].y_e);
            e_ship[ee].shoot(renderer, speed2);
        }
    }
    if((time>30 && time<100)||(time>250 && time<320)){
        for(int ee=0; ee<num_enemy; ee++){
            if(time%15==0){e_ship[ee].moveHorizontal=true;}
            else e_ship[ee].moveHorizontal=false;
        }
    }
    int _x=rand()%(SCREEN_WIDTH-DIAMOND_WEIGHT);

    if((time>10 && time <50) || (time>100 && time<300)){
        for(int dd=0; dd<num_diamonds; dd++){
            diamonds[dd].simple_move(_x);
            diamonds[dd].render(renderer, diamonds[dd].ob_rect.x, diamonds[dd].ob_rect.y);
        }
    }

    if((time>30&&time<45) || (time>150&&time<200) || (time>250&&time<280)){
        Life.simple_move(_x);
        Life.render(renderer, Life.ob_rect.x, Life.ob_rect.y);
    }
}


void Play_Game(){

    load_game_elements();
    if(Menu_Game()){
        //play game//
        while(!quit)
        {
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

            g_score.content=str_mark;
            g_score.LoadFromRenderTexture(g_font, renderer);
            g_score.renderText(renderer, 2, 10);
            //DIAMONDS
            NUM_DIAMONDS.render(renderer, 300, 10);
            amount_diamonds.content=to_string(amount_d);
            amount_diamonds.LoadFromRenderTexture(g_font, renderer);
            amount_diamonds.renderText(renderer, 340, 10);
        ///////////////////////////////////////////////////////////////////////
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT ){
                    quit=true;
                }
                HYPERION.InputAction(e, renderer);
            }

            object_appear(time_val);
            //Render spaceship
            HYPERION.move();
            HYPERION.render(renderer, HYPERION.x_, HYPERION.y_);
            HYPERION.shoot(renderer);

            //collect reward
            if(count_life>=1){
                if(Life.blt_checkCollision(HYPERION.ob_rect)){
                    Life.set_position_r(SCREEN_WIDTH/time_val);
                    count_life++;
                    cout<<"Your number of lifes: "<<count_life<<endl;
                }
                for(int d_c=0; d_c<num_diamonds; d_c++){
                    if(diamonds[d_c].blt_checkCollision(HYPERION.ob_rect)){
                        diamonds[d_c].set_position_r(SCREEN_WIDTH/3, -(d_c+1)*(DIAMOND_WEIGHT+10));
                        amount_d++;
                    }
                }
            }
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
                    e_ship[e_c].set_position();
                    e_ship[e_c].set_bullet_position();
                    Mix_PlayChannel( -1, ship_die, 0 );
                    count_life--;
                    cout<<"Your number of lifes: "<<count_life<<endl;
                }
                if(count_life<1){
                    cout<<endl<<endl<<"   GAME OVER!"<<endl<<endl<<"Your score is: "<<mark<<endl;
                    quit=true;
                    End_Game();
                    break;
                }
            }

            SDL_RenderPresent(renderer);
        }
    }
}

void End_Game(){
    A_Text your_score;
    your_score.set_color(0, 255, 0);
    your_score.content=to_string(mark);
    your_score.LoadFromRenderTexture(g_font, renderer);

    int x_text=90;
    if(win){
        text_in_the_end.loadImg("images//Win_game.png", renderer, 400, 150);
        x_text=60;
    }else text_in_the_end.loadImg("images//game_over.png", renderer, 300, 100);

    bool q=false;
    while(!q){
        SDL_RenderClear( renderer );
        g_menu_end.render(renderer, 0, 0);
        text_in_the_end.render(renderer, x_text, 100);
        your_score.renderText(renderer, 194, 352);
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_KEYDOWN){
                q=true;
                break;
            }
        }
    }

}
void close(){

    //Free the music
	Mix_FreeMusic( g_music );
	g_music = NULL;
	//Free the sound effects
	Mix_FreeChunk( ship_die );
    ship_die=NULL;
}
