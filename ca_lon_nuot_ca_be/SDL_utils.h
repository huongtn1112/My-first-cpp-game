#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,  const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
SDL_Texture *LoadTextture(string path, SDL_Renderer *renderTarget);
#endif
