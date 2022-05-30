
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
using namespace std;



const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Play game";
        int STEP_DELAY = 40;

struct Box{
    int x, y;
    int  size ;
    int stepX = 0;
    int stepY = 0;

    Box(int _x, int _y, int _size) : x(_x), y(_y), size(_size){}

     void render(SDL_Renderer* renderer)
     {
         SDL_Rect filled_rect;
        filled_rect.x = x;   // vi tri hinh
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // green
        SDL_RenderFillRect(renderer, &filled_rect);
     }
     void move()
     {
         x += stepX;
         y += stepY;
         //cout << x << " " << y << endl;

     }
     void turnLeft()
     {
         stepX = -5;
         stepY = 0;
     }
     void turnRight()
     {
         stepX = 5;
         stepY = 0;
     }
     void turnDown()
     {
         stepY = 5;
         stepX = 0;
     }
     void turnUp()
     {
         stepY = -5;
         stepX = 0;
     }
     bool inside(int minX, int minY, int maxX, int maxY)
    {
            return(minX <= x && minY <= y && x+size <= maxX && y+size <= maxY);
    }
    bool impactFood(Box food)
    {
        if(food.inside(x, y, x+size, y+size)) {
            return true;
        }
        return false;
    }
    void change_location()
    {
        x = rand() % 1100;
        y = rand() % 500;
    }
    bool va_cham(Box b)
    {
        int a = b.x -3; // Phai cham 1 ty thi moi an duoc
        int m = b.y -3;
        if(x + size < a || x > a + b.size || y + size < m || y > m + b.size)
        {
            return false;
        }
        else return true;
    }
};

Box fish_rand(int size)
{
    int x = rand() % 1000;
    int y = rand() % 500;
    Box f(x,y,size);
    return f;

}
void check_mark(int &mark, Box &b)
{
    if(mark >= 100 && b.size == 10) b.size += 10;
    if(mark >= 500 && b.size == 20) b.size += 10;
    if(mark >= 1000 && b.size == 30) b.size +=10;

}
int main(int argc, char* argv[])
{

    srand((int) time(0));
    int mark = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *backgroundImage = NULL;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Your drawing code here
     Box box(50, 50, 10);
     Box Fish[10] = {fish_rand(10), fish_rand(10), fish_rand(10), fish_rand(10), fish_rand(20), fish_rand(20), fish_rand(20), fish_rand(30),
                    fish_rand(30),fish_rand(40)};


    ////
     SDL_Event e;
     backgroundImage = LoadTextture("img//day_bien.png", renderer);
     bool Gameover = false;


     while(!Gameover)
     {
        if(!box.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) Gameover = true;
        box.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // trang
        SDL_RenderClear(renderer); // xóa màn hình
        SDL_RenderCopy(renderer, backgroundImage, NULL, NULL);

        box.render(renderer); // ve hinh
        // SDL_RenderCopy(renderer, text, NULL, &textRect);
        //Ca an thit
        for(int i=0; i<10; i++)
        {
             if(box.va_cham(Fish[i]) )
             if(box.size < Fish[i].size){
                Gameover = true;
             }
             else
                {
                    Fish[i].change_location();
                    mark+=Fish[i].size;
                }
        Fish[i].render(renderer);
        }
        check_mark(mark, box);


        ////
        SDL_RenderPresent(renderer);
        SDL_Delay(STEP_DELAY);
        if ( SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) Gameover = true;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE:  break;
        		case SDLK_LEFT: box.turnLeft(); break;
            	case SDLK_RIGHT:  box.turnRight(); break;
            	case SDLK_DOWN:  box.turnDown(); break;
            	case SDLK_UP:   box.turnUp(); break;
        		default: break;
			}
        }


     }

    cout << "Diem cua ban: " << mark;
    // use SDL_RenderPresent(renderer) to show it
    SDL_DestroyTexture(backgroundImage);
    waitUntilKeyPressed();
    quitSDL(window, renderer);



    return 0;
}

