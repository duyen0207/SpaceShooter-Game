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
Mix_Chunk* eat_money=NULL;
SDL_Event e;
    //main elements in game
    BaseObjects g_background;
    BaseObjects g_menu;
    BaseObjects g_menu_end;
    BaseObjects text_in_the_end;
            //CHARACTERS AND ITEMS
            Spaceship HYPERION;
            BaseObjects HOME;
            Enemies e_ship[num_enemy];
            Enemies ENEMY_LV_S; Bullet BULLETS_BOSS[num_bullet_of_boss]; int life_of_enemy_S=30;

            Reward coins[num_coins]; BaseObjects NUM_COINS; A_Text amount_coins;
            Reward Life;
            Reward Power;
                //additional elements
                bool win=false;
                bool quit = false;
                int scrollingOffset=0;
                A_Text g_score; Uint32 mark=0;
                A_Text your_score;

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
    load_wav_sound(eat_money, "sound_effect//beep.wav");
    //SCORE
    g_score.set_color(0,255,255);
    NUM_COINS.loadImg("images//money.png", renderer, COIN_WEIGHT, COIN_HEIGHT);
    amount_coins.set_color(0, 255, 255);
        //REWARD
        Life.loadImg("images//support_life.png", renderer, LIFE_WEIGHT, LIFE_HEIGHT);
        Power.loadImg("images//power.png", renderer, POWER_WEIGHT, POWER_HEIGHT);

        for(int r=0; r<num_coins; r++){
            coins[r].loadImg("images//money.png", renderer, COIN_WEIGHT, COIN_HEIGHT);
            coins[r].set_position_r(SCREEN_WIDTH/2, -(r+1)*(COIN_HEIGHT+5));
        }

    //spaceship
    HYPERION.loadImg("images//spaceship.png", renderer, SHIP_WIDTH, SHIP_HEIGHT);
    HOME.loadImg("images//earth.png", renderer, EARTH_WIDTH, EARTH_WIDTH);
    HOME.ob_rect.y=-SCREEN_HEIGHT/2;
    //enemies
    ENEMY_LV_S.loadImg("images//enemy_lv_S.png",renderer, BOSS_WIDTH, BOSS_HEIGHT);
    ENEMY_LV_S.e_bullet.loadImg("images//big_bullet.png",renderer, SS_W, SS_H);
    for(int i=0; i<num_bullet_of_boss; i++){
        BULLETS_BOSS[i].loadImg("images//big_bullet.png",renderer, SS_W, SS_H);
        if(i<=num_bullet_of_boss/2){
            BULLETS_BOSS[i].set_position_(ENEMY_LV_S.x_e, (ENEMY_LV_S.y_e+BOSS_HEIGHT+i*SS_H));
        }
        else BULLETS_BOSS[i].set_position_((ENEMY_LV_S.x_e+BOSS_WIDTH*3/4), (ENEMY_LV_S.y_e+BOSS_HEIGHT+i*SS_H));
    }
    for(int e=0; e<num_enemy; e++){
        e_ship[e].loadImg("images//aaa.png", renderer, E_WIDTH, E_HEIGHT);
        e_ship[e].set_position();
        e_ship[e].e_bullet.loadImg("images//e_bullet.png", renderer, B_W, B_H);
    }
}

void object_appear(Uint32 &time){

//HOME
    if(life_of_enemy_S<1){
        HOME.earth_move();
        HOME.render(renderer, (SCREEN_WIDTH-EARTH_WIDTH)*0.5, HOME.ob_rect.y);
    }
//SUPPORT
    int _x=rand()%(SCREEN_WIDTH-COIN_WEIGHT);
    if((time>10 && time <70) || (time>100 && time<200)){
        for(int dd=0; dd<num_coins; dd++){
            coins[dd].simple_move(_x);
            coins[dd].render(renderer, coins[dd].ob_rect.x, coins[dd].ob_rect.y);
        }
    }

    if((time>30&&time<40) || (time>150&&time<160) || (time>250&&time<265)){
        Life.simple_move(_x);
        Life.render(renderer, Life.ob_rect.x, Life.ob_rect.y);
    }

    if(time>3){
        Power.simple_move(_x+10);
        Power.render(renderer, Power.ob_rect.x, Power.ob_rect.y);
    }
//SMALL ENEMIES
    if(time>5){
        for(int ee=0; ee<num_enemy; ee++){
            e_ship[ee].HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, speed_e);
            e_ship[ee].render(renderer, e_ship[ee].x_e, e_ship[ee].y_e);
            e_ship[ee].shoot(renderer, speed2);
        }
    }

    for(int ee=0; ee<num_enemy; ee++){
        if((time>20 && time<60)||(time>110 && time<150)){
            e_ship[ee].moveHorizontal=true;
        }else e_ship[ee].moveHorizontal=false;
    }
//BOSS
    if(time>0){
        ENEMY_LV_S.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT/2, speed_e);
        ENEMY_LV_S.render(renderer, ENEMY_LV_S.x_e, ENEMY_LV_S.y_e);
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
            //COINS
            NUM_COINS.render(renderer, 300, 10);
            amount_coins.content=to_string(HYPERION.coins_amount);
            amount_coins.LoadFromRenderTexture(g_font, renderer);
            amount_coins.renderText(renderer, 340, 10);
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
            HYPERION.after_get_power();

//SUPPORT_ITEM
            if(HYPERION.count_life>=1){

                if(HYPERION.blt_checkCollision(Power.ob_rect)){
                    Power.set_position_r(SCREEN_WIDTH/(rand()%5+1));
                    HYPERION.collected_power++;
                }
                if(Life.blt_checkCollision(HYPERION.ob_rect)){
                    Life.set_position_r(SCREEN_WIDTH/(rand()%10+1));
                    HYPERION.count_life++;
                    cout<<"Your number of lifes: "<<HYPERION.count_life<<endl;
                }
                for(int d_c=0; d_c<num_coins; d_c++){
                    if(coins[d_c].blt_checkCollision(HYPERION.ob_rect)){
                        int random=rand()%10+1;
                        coins[d_c].set_position_r(SCREEN_WIDTH/random, -(d_c+1)*(COIN_WEIGHT+10));
                        HYPERION.coins_amount++;
                        Mix_PlayChannel( -1, eat_money, 0 );
                    }
                }
            }
            //check collision between spaceship, bullets and enemy

            if(time_val>0){

                for(int k=0; k<HYPERION.bullet_list.size(); k++){
                    Bullet* b_col= HYPERION.bullet_list.at(k);
                    if(b_col->blt_checkCollision(ENEMY_LV_S.ob_rect)){
                        mark+=2000;
                        b_col->is_move=false;
                        ENEMY_LV_S.Boss_die(life_of_enemy_S, b_col->type);

                        HYPERION.bullet_list.erase(HYPERION.bullet_list.begin()+k);
                        if(b_col!=NULL){
                            delete b_col;
                            b_col=NULL;
                        }
                    }
                }
                if(HYPERION.spac_checkCollision(ENEMY_LV_S.ob_rect)){
                    Mix_PlayChannel( -1, ship_die, 0 );
                    HYPERION.die();
                    life_of_enemy_S--;
                }
                if(life_of_enemy_S<1){
                    if(HYPERION.blt_checkCollision(HOME.ob_rect)){
                        win=true;
                    }
                }
            }

            for(int e_c=0; e_c<num_enemy; ++e_c){
                //bullet of spaceship and enemies
                for(int k=0; k<HYPERION.bullet_list.size(); k++){
                    Bullet* b_col= HYPERION.bullet_list.at(k);
                    if(b_col->blt_checkCollision(e_ship[e_c].ob_rect)){
                        mark+=10;
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
                    HYPERION.die();
                }
                if(HYPERION.count_life<1 || win){
                    break;
                }
            }
            if(HYPERION.count_life<1 || win){
                quit=true;
                End_Game();
            }

            SDL_RenderPresent(renderer);
        }
    }
}

void End_Game(){

    your_score.set_color(0, 255, 0);
    your_score.content=to_string(mark);
    your_score.LoadFromRenderTexture(g_font, renderer);

    BaseObjects STAR_NUM; const int STAR_WIDTH=105, STAR_HEIGHT=35;

    int x_text=90;
    if(win){
        text_in_the_end.loadImg("images//Win_game.png", renderer, 400, 150);
        x_text=60;

        if(HYPERION.coins_amount>200){STAR_NUM.loadImg("images//3_stars.png", renderer, STAR_WIDTH, STAR_HEIGHT);}
        else if(HYPERION.coins_amount>100){STAR_NUM.loadImg("images//2_stars.png", renderer, STAR_WIDTH, STAR_HEIGHT);}
        else if(HYPERION.coins_amount>20) {STAR_NUM.loadImg("images//1_star.png", renderer, STAR_WIDTH, STAR_HEIGHT);}
        else STAR_NUM.loadImg("images//no_star.png", renderer, STAR_WIDTH, STAR_HEIGHT);
    }else text_in_the_end.loadImg("images//game_over.png", renderer, 300, 100);

    bool q=false;
    while(!q){
        SDL_RenderClear( renderer );
        g_menu_end.render(renderer, 0, 0);
        text_in_the_end.render(renderer, x_text, 80);
        if(win){STAR_NUM.render(renderer, 170, 260);}
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
	Mix_FreeChunk( eat_money);
    ship_die=NULL;
    eat_money=NULL;
}
