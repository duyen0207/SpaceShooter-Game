#ifndef Base_Functions_h
#define Base_Functions_h

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Space Shooter";
const int FONT=15;

const int RED = 255;
const int GREEN = 255;
const int BLUE = 255;

//functions to set and close SDL
void logSDLError(ostream& os, const string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, TTF_Font* &g_font, int screenWidth, int screenHeight, string windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();
//////////////////////////////////////////

void load_mp3_sound(Mix_Music* &g_music, const char* m_path);



#endif // Base_Functions_h
