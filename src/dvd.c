//created: October 31 2019
//last update: January 12 2020
//written by moxniso

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef _WIN32
#include <unistd.h>
#endif

typedef enum {false, true} bool; //stdbool is for suckers!

#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (500)
#define SCROLL_SPEED (300)  //speed in pixels per second
#define SPEED (150)
#define TRUE 1
#define FALSE 0
#define MISSINGLOGO printf("the .png image of the DVD logo isn't found.\nPlease run this executable in the same directory where the dvd logo is.\n");

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("aesthetic dvd player vision 2007",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       600, 500, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    #ifndef _WIN32
    if (access("dvd2.png", R_OK) != 0) { MISSINGLOGO return 1; }
    #endif
    #ifdef _WIN32
    if (!fopen("dvd2.png", 'rb')) { MISSINGLOGO return 1; }
    #endif
    
    else {
    SDL_Surface* surface = IMG_Load("dvd2.png");
    if (!surface)
    {
        printf("error creating surface for DVD logo: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* logo = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!logo)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Rect lp; //lp standing for logo properties
    SDL_QueryTexture(logo, NULL, NULL, &lp.w, &lp.h);
    lp.w /= 8;
    lp.h /= 8;
    float x_pos = (WINDOW_WIDTH - lp.w) / 2;
    float y_pos = (WINDOW_HEIGHT - lp.h) / 2;
    float y_vel = SPEED;
    float x_vel = SPEED;

bool exit = FALSE;
SDL_Event input;
while(!exit) {
    SDL_PollEvent(&input);
    if (input.type == SDL_QUIT) {
       exit = TRUE; 
    }
    else {

    if (x_pos <= 0) {
        x_pos = 0;
        x_vel = -x_vel;
    }
    if (y_pos <= 0) {
        y_pos = 0;
        y_vel = -y_vel;
    }
    if (x_pos >= WINDOW_WIDTH - lp.w) {
        x_pos = WINDOW_WIDTH - lp.w;
        x_vel = -x_vel;
    }
    if (y_pos >= WINDOW_HEIGHT - lp.h) {
        y_pos = WINDOW_HEIGHT - lp.h;
        y_vel = -y_vel;
    }

    x_pos += x_vel / 60;
    y_pos += y_vel / 60;
    lp.y = (int) y_pos;
    lp.x = (int) x_pos;

    SDL_RenderClear(rend);

    SDL_RenderCopy(rend, logo, NULL, &lp);
    
    // draw the image to the window
    SDL_RenderCopy(rend, logo, NULL, &lp);
    SDL_RenderPresent(rend);

    SDL_Delay(1000/60);
    }
}
    SDL_DestroyTexture(logo);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("Exit successful.\n");
    return 0;
    }
}
