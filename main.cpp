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

class Rect
{
    public:
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
        uint32_t color;
        Rect(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, uint32_t _color){
            x = _x;
            y = _y;
            width = _width;
            height = _height;
            color = _color;
        }
        Rect(){
            x = 0;
            y = 0;
            width = 0;
            height = 0;
            color = 0xFFFFFF;
        }


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

void bitPrint(uint32_t a) {
     for(int i=UINT32_WIDTH; i>0; i--) {
        if(i%4==0){
            printf(" ");
        }
         printf("%d", (a>>i-1)&1);   
         }
        
        printf("\n");
    }

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

void setFrameColor(uint32_t* frame, uint32_t _rgb){
    for(int i=0; i<WIN_W*WIN_H; i++){
        frame[i] = _rgb;
    }
}

void drawRectToFrame(uint32_t* frame, Rect rec){
    for(int y=rec.y; y<rec.y+rec.height; y++){
        for(int x=rec.x; x<rec.x+rec.width; x++){
            frame[x + y*WIN_W] = rec.color;
        }
    }
}

int main()
{
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

    Rect r = Rect(10, 10, 100, 100, 0x00FF00);

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
                r.y -= 10;
                break;
            case SDLK_DOWN:
                // WIN_H += 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                r.y += 10;
                break;
            case SDLK_LEFT:
                // WIN_W -= 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                r.x -= 10;
                break;
            case SDLK_RIGHT:
                // WIN_W += 10;
                // SDL_SetWindowSize(window, WIN_W, WIN_H);
                r.x += 10;
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

            //tile((uint32_t*)frame);
            setFrameColor((uint32_t*)frame, 0);
            drawRectToFrame((uint32_t*)frame, r);

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


    
        
    } while(e.type != SDL_QUIT);



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