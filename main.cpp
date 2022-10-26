#include <iostream>
#include <fstream>
#include <vector>

#include <ctime>
#include <cstdlib>

#include <SDL2/SDL.h>


const unsigned int WIN_W = 800;
const unsigned int WIN_H = 600;

const unsigned int TILE_SIZE = 100;

uint32_t packRGB(uint8_t _r, uint8_t _g, uint8_t _b){
    uint32_t _rgb = 0;

    _rgb   = _r;
    _rgb <<=  8;
    _rgb  |= _g;
    _rgb <<=  8;
    _rgb  |= _b;
    return _rgb;
}

void bitPrint(uint32_t a) {
     for(int i=UINT32_WIDTH; i>0; i--) {
        if(i%4==0){
            printf(" ");
        }
         printf("%d", (a>>i-1)&1);   
         }
        
        printf("\n");
    }


int main()
{
    // uint32_t frame[WIN_W][WIN_H] = {};

    // // Set tiles with random color
    // std::srand(std::time(nullptr));
    // uint32_t color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
    // for(int y=0; y<WIN_H; y++){
    //     for(int x=0; x<WIN_W; x++){
    //         if(x%TILE_SIZE==0 && y%TILE_SIZE==0){
    //             color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
    //             frame[x][y] = color;
    //         } else{
    //             if(y%TILE_SIZE!=0){
    //                 frame[x][y] = frame[x][y-1];
    //             }
    //             if(x%TILE_SIZE!=0){
    //                 frame[x][y] = frame[x-1][y];
    //             }
    //         }
    //     }
    // }

    /*
    SDL_CreateRGBSurfaceFrom(pixels,10, 10, 24, 10*3, 0xFF0000, 0x00FF00, 0x0000FF, 0);

			SDL_BlitSurface(pixels, NULL, screenSurface, NULL);
    */

    uint32_t frame[WIN_W*WIN_H] = {};

    // for(int i=0; i<WIN_W*WIN_H; i++){
    //     frame[i] = 0xFF0000FF;
    // }


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

    // SDL Setup
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* offscreen = NULL;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize ! SDL_Error: %s", SDL_GetError());
        return -1;
	}

    // Create window
    window = SDL_CreateWindow("rc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);


    if(window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);   
    
    /*
    SDL_Surface* SDL_CreateRGBSurfaceFrom(void *pixels,
                                int width,
                                int height,
                                int depth,
                                int pitch,
                                Uint32 Rmask,
                                Uint32 Gmask,
                                Uint32 Bmask,
                                Uint32 Amask);
    */

    offscreen = SDL_CreateRGBSurfaceFrom(frame, WIN_W, WIN_H, 32, 4*WIN_W, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
    if(offscreen == NULL){
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_BlitSurface(offscreen, NULL, screenSurface, NULL);
    SDL_FreeSurface(offscreen);

    std::cout << SDL_GetError();

    

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Hack to get window to stay up
    SDL_Event e; bool quit = false; while (quit == false){while(SDL_PollEvent(&e)){if(e.type == SDL_QUIT) quit = true;}}

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();




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