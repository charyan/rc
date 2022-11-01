#include <iostream>
#include <fstream>
#include <vector>

#include <ctime>
#include <cstdlib>

#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "headers/Rect.h"
#include "headers/Player.h"
#include "headers/Renderer.h"
#include "headers/RayCaster.h"

#define PI 3.14

unsigned int WIN_W = 800;
unsigned int WIN_H = 600;

float PLAYER_SPEED = 1.;

const unsigned int TILE_SIZE = 100;

unsigned int GAMEMAP_WIDTH = 40;
unsigned int GAMEMAP_HEIGHT = 20;
unsigned int GAMEMAP[20*40] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

struct Point{
    uint32_t x;
    uint32_t y;
};

uint32_t packRGB(uint8_t _r, uint8_t _g, uint8_t _b){
    uint32_t _rgb = 0;

    _rgb   = _r;
    _rgb <<=  8;
    _rgb  |= _g;
    _rgb <<=  8;
    _rgb  |= _b;
    return _rgb;
}

/** 
 * @brief Print to stdout a string containing the bits of an uint32_t
 * @param a uint32_t variable to print
 */
void bitPrint(uint32_t a) {
     for(int i=UINT32_WIDTH; i>0; i--) {
        if(i%4==0){
            printf(" ");
        }
         printf("%d", (a>>i-1)&1);   
         }
        
        printf("\n");
    }

/**
 * @brief Draw tiles with a random color on frame
 *        The size of the tiles is defined by the global var TILE_SIZE in px
 * 
 * @param frame The frame to draw the tiles on
 */
void tile(uint32_t* frame){
    // Set tiles with random color
    std::srand(std::time(nullptr));
    uint32_t color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
    for(int y=0; y<WIN_H; y++){
        for(int x=0; x<WIN_W; x++){
            if(x%TILE_SIZE==0 && y%TILE_SIZE==0){
                color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
                frame[x+y*WIN_W] = color;
            } else{
                if(y%TILE_SIZE!=0){
                    frame[x+y*WIN_W] = frame[x+(y-1)*WIN_W];
                }
                if(x%TILE_SIZE!=0){
                    frame[x+y*WIN_W] = frame[(x-1)+y*WIN_W];
                }
            }
        }
    }
}





int main()
{
    SDL_Event e;

   

    Player player = {0., {400,300,10,10,0x00FF00}};
    
    Renderer rend(WIN_W, WIN_H);
    RayCaster rc(rend);
    

    bool key_w = false;
    bool key_a = false;
    bool key_s = false;
    bool key_d = false;
    bool key_left = false;
    bool key_right = false;
    do {
        uint64_t t1 = SDL_GetTicks64();
        uint64_t t2 = 0;

        float nx = 0.;
        float ny = 0.;
        float na = 0.;
        while(SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)){
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_w:
                    key_w = true;
                    break;
                case SDLK_a:
                    key_a = true;
                    break;
                case SDLK_s:
                    key_s = true;
                    break;
                case SDLK_d:
                    key_d = true;
                    break;
                case SDLK_LEFT:
                    key_left = true;
                    break;
                case SDLK_RIGHT:
                    key_right = true;
                    break;
                case SDLK_LSHIFT:
                    PLAYER_SPEED = 2.;
                    break;     
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                case SDLK_w:
                    key_w = false;
                    break;
                case SDLK_a:
                    key_a = false;
                    break;
                case SDLK_s:
                    key_s = false;
                    break;
                case SDLK_d:
                    key_d = false;
                    break;
                case SDLK_LEFT:
                    key_left = false;
                    break;
                case SDLK_RIGHT:
                    key_right = false;
                    break;
                case SDLK_LSHIFT:
                    PLAYER_SPEED = 1.;
                    break;     
                default:
                    break;
                }
            default:
                break;
            }
        }

        if(key_w){
            nx = PLAYER_SPEED*cos(player.angle);
            ny = -PLAYER_SPEED*sin(player.angle);
        }

        if(key_a){
            nx = PLAYER_SPEED*cos(player.angle+PI/2);
            ny = -PLAYER_SPEED*sin(player.angle+PI/2);
        }

        if(key_s){
            nx = -PLAYER_SPEED*cos(player.angle);
            ny = PLAYER_SPEED*sin(player.angle);
        }

        if(key_d){
            nx = -PLAYER_SPEED*cos(player.angle+PI/2);
            ny = PLAYER_SPEED*sin(player.angle+PI/2);
        }

        if(key_left){
            na += PI/120;
        }

        if(key_right){
            na -= PI/120;
        }

        player.x     += nx;
        player.y     += ny;
        player.angle += na;

        uint32_t frame[rend.winW*rend.winH];
        uint32_t rcView[rend.winW*rend.winH];
        uint32_t windowFrame[rend.winW*rend.winH*2];
        rend.frame = frame;
        rend.rcView = rcView;
        rend.windowFrame = windowFrame;
        rend.setFrameColor(0);
        rend.setFrameColor(0, rcView);


        // castRay(rend, player);
        rc.applyGamemap(GAMEMAP, GAMEMAP_WIDTH,GAMEMAP_HEIGHT);
        rc.castRay(player);
        rend.drawRectToFrame(Rect(player.getX(), player.getY(), player.r.width, player.r.height, player.r.color));
        rc.drawRayCastView(player);


        // player.angle += M_1_PIf32/24;

        rend.updateWindow();

        t2 = SDL_GetTicks64();
    
        // printf("deltaT[s]: %f | fps: %4.1f\r", (t2-t1)/1000., 1/((t2-t1)/1000.));
        // printf("x: %d, y: %d, angle: %f, cos: %f, sin: %f\r", player.r.x, player.r.y, player.angle, cos(player.angle), sin(player.angle));

        // rend.saveFrameToFile();
        // break;
        
    } while(e.type != SDL_QUIT);
    rend.quit();

    



    return 0;
}