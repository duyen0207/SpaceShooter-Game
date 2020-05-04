#include "BaseFunctions.h"

    //initialize and destroy SDL////////////////////////////////////
void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, TTF_Font* &g_font,
	int screenWidth, int screenHeight, string windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    //Initialize SDL_ttf
    if(TTF_Init()==-1){
        cout<<"Error to initialize font"<<endl;
    }
    else{
        g_font=TTF_OpenFont("font//lazy.ttf", FONT);
        if(g_font == NULL){
            cout<<"Can't find the font."<<endl;
        }
    }
     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
}


void quitSDL(SDL_Window* window, SDL_Renderer* &renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
////////////////////////////////////////////

void load_mp3_sound(Mix_Music* &g_music, const char* m_path){
    g_music = Mix_LoadMUS(m_path);
    if(g_music==NULL){
        cout<<"Can't find music."<<endl;
    }
}

