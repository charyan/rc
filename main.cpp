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

float PLAYER_SPEED = 5.;

const unsigned int TILE_SIZE = 100;

unsigned int GAMEMAP[36] = {
    1,1,1,0,0,0,
    1,0,0,0,0,0,
    1,0,0,0,0,0,
    1,0,0,0,0,1,
    1,1,1,1,1,1
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
    SDL_Event ecpy;

   

    Player player = {0., {400,300,10,10,0x00FF00}};
    
    Renderer rend(WIN_W, WIN_H);
    RayCaster rc(rend);
    

    do {
        uint64_t t1 = SDL_GetTicks64();
        uint64_t t2 = 0;

        SDL_PollEvent(&e);
 
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                player.x += PLAYER_SPEED*cos(player.angle);
                player.y -= PLAYER_SPEED*sin(player.angle);
                break;

            case SDLK_a:
                player.x += PLAYER_SPEED*cos(player.angle+PI/2);
                player.y -= PLAYER_SPEED*sin(player.angle+PI/2);
                break;

            case SDLK_s:
                player.x -= PLAYER_SPEED*cos(player.angle);
                player.y += PLAYER_SPEED*sin(player.angle);
                break;

            case SDLK_d:
                player.x -= PLAYER_SPEED*cos(player.angle+PI/2);
                player.y += PLAYER_SPEED*sin(player.angle+PI/2);
                break;
            case SDLK_LEFT:
                player.angle += PI/6;
                break;
            case SDLK_RIGHT:
                player.angle -= PI/6;
                break;
            case SDLK_SPACE:
                SDL_SetWindowSize(rend.window, rend.winW+=20, rend.winH+=20);
                break;     
            
            default:
                break;
            }
            break;
        default:
            break;
        }




        uint32_t frame[rend.winW*rend.winH];
        rend.frame = frame;
        rend.setFrameColor(0);


        // castRay(rend, player);
        rc.applyGamemap(GAMEMAP, 6,6);
        rc.castRay(player);
        rend.drawRectToFrame(Rect(player.getX(), player.getY(), player.r.width, player.r.height, player.r.color));


        // player.angle += M_1_PIf32/24;

        rend.updateWindow();

        t2 = SDL_GetTicks64();
    
        //printf("deltaT[s]: %f | fps: %4.1f\r", (t2-t1)/1000., 1/((t2-t1)/1000.));
        printf("x: %d, y: %d, angle: %f, cos: %f, sin: %f\r", player.r.x, player.r.y, player.angle, cos(player.angle), sin(player.angle));

        // rend.saveFrameToFile();
        // break;
        
    } while(e.type != SDL_QUIT);
    rend.quit();

    



    return 0;
}