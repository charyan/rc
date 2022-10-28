/**
 * Todo:
 *  - move SDL code from main.ccp to Renderer
 *  - create utils.cpp/.h
 *  - put castRay in 
 */

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

unsigned int WIN_W = 800;
unsigned int WIN_H = 600;

const unsigned int TILE_SIZE = 100;

uint32_t GAMEMAP[100] = {
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},{0x00000000},
    {0xFF000000},{0xFF000000},{0xFF000000},{0xFF000000},{0xFF000000},{0xFF000000},{0xFF000000},{0x00000000},{0x00000000},{0x00000000}
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


// void setFrameColor(uint32_t* frame, uint32_t _rgb){
//     for(int i=0; i<WIN_W*WIN_H; i++){
//         frame[i] = _rgb;
//     }
// }

// void drawRectToFrame(uint32_t* frame, Rect rec){
//     printf("{x: %d, y:%d, width:%d, height:%d, color:%x}\n", rec.x, rec.y, rec.width, rec.height, rec.color);
//     for(int y=rec.y; y<rec.y+rec.height; y++){
//         for(int x=rec.x; x<rec.x+rec.width; x++){
//             frame[x + y*WIN_W] = rec.color;
//         }
//     }
// }



// // TODO MAKE IT WORK
// void applyTileMapToFrame(uint32_t* frame){
//     uint32_t color = 0xFFFFFF;
//     uint32_t tileHeight = WIN_H/100;
//     uint32_t tileWidth = WIN_W/100;
    
//     for(int y=0; y<10; y++){
//         for(int x=0; x<10; x++){
//             if(GAMEMAP[x+y*10] != 0){
//                 drawRectToFrame(frame, Rect(x*tileWidth, y*tileHeight, tileWidth, tileHeight, 0xFFFFFF));
//             }
//         }
//     }
// }

// void plotLineHigh(uint32_t* frame, int x0, int y0, int x1, int y1){
//     int dx = x1 - x0;
//     int dy = y1 - y0;
//     int xi = 1;
//     if(dx < 0){
//         xi = -1;
//         dx = -dx;
//     }
//     int D = (2*dx) - dy;
//     int x = x0;

//     for(int y=y0; y<y1; y++){
//         frame[x+y*WIN_W] = 0xFFFFFF;
//         if(D>0){
//             x += xi;
//             D += 2*(dx-dy);
//         } else {
//             D += 2*dx;
//         }
//     }
// }

// void plotLineLow(uint32_t* frame, int x0, int y0, int x1, int y1){
//     int dx = x1 - x0;
//     int dy = y1 - y0;
//     int yi = 1;

//     if(dy<0){
//         yi = -1;
//         dy = -dy;
//     }
//     int D = (2*dy)-dx;
//     int y = y0;
    
//     for(int x=x0; x<x1; x++){
//         frame[x+y*WIN_W] = 0xFFFFFF;
//         if(D>0){
//             y += yi;
//             D += 2*(dy-dx);
//         } else {
//             D += 2*dy;
//         }
//     }
// }

// /**
//  * @brief Bresenham's_line_algorithm
//  * 
//  * @param frame 
//  * @param x0 
//  * @param y0 
//  * @param x1 
//  * @param y1 
//  */
// void plotLine(uint32_t* frame, int x0, int y0, int x1, int y1){
//     if(abs(y1-y0)<abs(x1-x0)) {
//         if(x0>x1){
//             plotLineLow(frame, x1,y1,x0,y0);
//         } else {
//             plotLineLow(frame, x0,y0,x1,y1);
//         }
//     } else {
//         if(y0>y1){
//             plotLineHigh(frame, x1,y1,x0,y0);
//         } else {
//             plotLineHigh(frame, x0,y0,x1,y1);
//         }
//     }
// }





void castRay(Renderer r, Player player){

    float x = player.r.x + 150*cos(player.angle);
    float y = player.r.y - 150*sin(player.angle);
    
    r.plotLine(player.r.x, player.r.y, int(x), int(y));

    r.plotLine(int(x), 0, int(x), int(y));
    r.plotLine(0, int(y), int(x), int(y));

    
    

}

int main()
{
    // SDL Setup
    // SDL_Window* window = NULL;
    // SDL_Surface* screenSurface = NULL;
    // SDL_Surface* offscreen = NULL;
    


    // if(SDL_Init(SDL_INIT_VIDEO) < 0)
	// {
	// 	printf("SDL could not initialize ! SDL_Error: %s", SDL_GetError());
    //     return -1;
	// }

    // // Create window
    // window = SDL_CreateWindow("rc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    // //SDL_SetWindowResizable(window, SDL_TRUE);

    // if(window == NULL) {
    //     printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    //     return -1;
    // }


    SDL_Event e;

    uint64_t t1 = SDL_GetTicks64();
    uint64_t t2 = 0;

    Player player = {0., {400,300,1,1,0x00FFFFFF}};
    //drawLine(frame, {0,0}, {800,600});
    
    Renderer rend(WIN_W, WIN_H);

    do {
        SDL_PollEvent(&e);
 
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                // WIN_H -= 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                player.r.y -= 10;
                
                break;
            case SDLK_DOWN:
                // WIN_H += 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                player.r.y += 10;
                
                break;
            case SDLK_LEFT:
                // WIN_W -= 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                player.r.x -= 10;
                
                break;
            case SDLK_RIGHT:
                // WIN_W += 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                player.r.x += 10;
                
                break;                
            
            default:
                break;
            }
            break;
        default:
            break;
        }
        
        uint32_t frame[WIN_W*WIN_H];
        rend.frame = frame;
        t2 = SDL_GetTicks64();

        // TODO FIX TIME

        if(t1-t2 >= 0){
            // // Get window surface
            // screenSurface = SDL_GetWindowSurface(window);

            // //tile((uint32_t*)frame);
            // setFrameColor((uint32_t*)frame, 0);
            // // applyTileMapToFrame((uint32_t*)frame);
            // drawRectToFrame((uint32_t*)frame, player.r);
            // //castRay((uint32_t*)frame, player);


            castRay(rend, player);
            
            player.angle += M_1_PIf32/24;

            //plotLine(frame, player.r.x, player.r.y, cos(player.angle), sin(player.angle));

            
            // offscreen = SDL_CreateRGBSurfaceFrom(frame, WIN_W, WIN_H, 32, 4*WIN_W, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
            // if(offscreen == NULL){
            //     printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
            //     return -1;
            // }

            // SDL_BlitSurface(offscreen, NULL, screenSurface, NULL);
            // SDL_FreeSurface(offscreen);

            // std::cout << SDL_GetError();

            

            // // Update the surface
            // SDL_UpdateWindowSurface(window);
            rend.updateWindow();
        } else {
            t1 = t2;
        }


    
        
    } while(e.type != SDL_QUIT);


    rend.quit();
    // // Destroy window
    // SDL_DestroyWindow(window);

    // // Quit SDL subsystems
    // SDL_Quit();


    // std::ofstream File("frame.ppm", std::ios::out | std::ios::binary);

    // File << "P6" << (uint8_t)0x0A << WIN_W << (uint8_t)0x20 << WIN_H << (uint8_t)0x0A << "255" << (uint8_t)0x0A;
    
    // for(int y=0; y<WIN_H; y++){
    //     for(int x=0; x<WIN_W; x++){
    //         // R
    //         File << (uint8_t)(frame[x][y]>>16);
    //         // G
    //         File << (uint8_t)((frame[x][y]>>8)&0x000000FF);
    //         // B
    //         File << (uint8_t)(frame[x][y]&0x000000FF);
    //     }
    // }
    
    // File.close();

    return 0;
}