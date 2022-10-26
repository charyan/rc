#include <iostream>
#include <fstream>
#include <vector>

#include <ctime>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

unsigned int WIN_W = 800;
unsigned int WIN_H = 600;

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
    //         if(x%TILE_SIZESDL_WINDOWEVENT_RESIZED=0 && y%TILE_SIZE==0){
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
    //SDL_SetWindowResizable(window, SDL_TRUE);

    if(window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }


    SDL_Event e;

    uint64_t t1 = SDL_GetTicks64();
    uint64_t t2 = 0;

    do {
        SDL_PollEvent(&e);
        // if(e.type == SDL_WINDOWEVENT){  
        //     if(e.window.event == SDL_WINDOWEVENT_RESIZED){
        //         WIN_W = SDL_GetWindowSurface(window)->w;
        //         WIN_H = SDL_GetWindowSurface(window)->h;

        //         printf("WIN_H %d", WIN_H);
        //         printf("WIN_W %d", WIN_W);
                
        //         continue;
        //     }
        // } else {
        //     SDL_SetWindowSize(window, WIN_W, WIN_H);
        // }

 
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                WIN_H -= 10;
                SDL_SetWindowSize(window, WIN_W, WIN_H);
                break;
            case SDLK_DOWN:
                WIN_H += 10;
                SDL_SetWindowSize(window, WIN_W, WIN_H);
                break;
            case SDLK_LEFT:
                WIN_W -= 10;
                SDL_SetWindowSize(window, WIN_W, WIN_H);
                break;
            case SDLK_RIGHT:
                WIN_W += 10;
                SDL_SetWindowSize(window, WIN_W, WIN_H);
                break;                
            
            default:
                break;
            }
            break;
        default:
            break;
        }
        
        uint32_t frame[WIN_W*WIN_H];
        t2 = SDL_GetTicks64();

        

        if(t1-t2 >= 1000){
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);  

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
        } else {
            t1 = t2;
        }
        
        //SDL_Delay(1000);

    
        
    } while(e.type != SDL_QUIT);


    // for(int i=0; i<WIN_W*WIN_H; i++){
    //     frame[i] = 0xFF0000FF;
    // }



    
 
    
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


    // Hack to get window to stay up
    //SDL_Event e; bool quit = false; while (quit == false){while(SDL_PollEvent(&e)){if(e.type == SDL_QUIT) quit = true;}}

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