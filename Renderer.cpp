#include "headers/Renderer.h"

void Renderer::plotLineHigh(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if(dx < 0){
        xi = -1;
        dx = -dx;
    }
    int D = (2*dx) - dy;
    int x = x0;

    for(int y=y0; y<y1; y++){
        frame[x+y*winW] = 0xFFFFFF;
        if(D>0){
            x += xi;
            D += 2*(dx-dy);
        } else {
            D += 2*dx;
        }
    }
}

void Renderer::plotLineLow(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if(dy<0){
        yi = -1;
        dy = -dy;
    }
    int D = (2*dy)-dx;
    int y = y0;
    
    for(int x=x0; x<x1; x++){
        frame[x+y*winW] = 0xFFFFFF;
        if(D>0){
            y += yi;
            D += 2*(dy-dx);
        } else {
            D += 2*dy;
        }
    }
}

/**
 * @brief Bresenham's_line_algorithm
 * 
 * @param frame 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 */
void Renderer::plotLine(int x0, int y0, int x1, int y1){
    if(abs(y1-y0)<abs(x1-x0)) {
        if(x0>x1){
            plotLineLow(x1,y1,x0,y0);
        } else {
            plotLineLow(x0,y0,x1,y1);
        }
    } else {
        if(y0>y1){
            plotLineHigh(x1,y1,x0,y0);
        } else {
            plotLineHigh(x0,y0,x1,y1);
        }
    }
}


void Renderer::setFrameColor(uint32_t _rgb){
    for(int i=0; i<winW*winH; i++){
        frame[i] = _rgb;
    }
}

void Renderer::drawRectToFrame(Rect rec){
    printf("{x: %d, y:%d, width:%d, height:%d, color:%x}\n", rec.x, rec.y, rec.width, rec.height, rec.color);
    for(int y=rec.y; y<rec.y+rec.height; y++){
        for(int x=rec.x; x<rec.x+rec.width; x++){
            frame[x + y*winW] = rec.color;
        }
    }
}

Renderer::Renderer(uint32_t _winW, uint32_t _winH){
    winW = _winW;
    winH = _winH;

    // SDL INIT
    window = NULL;
    screenSurface = NULL;
    offscreen = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize ! SDL_Error: %s", SDL_GetError());
        exit(1);
	}

    // Create window
    window = SDL_CreateWindow("rc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winW, winH, SDL_WINDOW_SHOWN);
    //SDL_SetWindowResizable(window, SDL_TRUE);

    if(window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }



}

void Renderer::updateWindow(){
    screenSurface = SDL_GetWindowSurface(window);
    
    offscreen = SDL_CreateRGBSurfaceFrom(frame, winW, winH, 32, 4*winW, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
    if(offscreen == NULL){
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_BlitSurface(offscreen, NULL, screenSurface, NULL);
    SDL_FreeSurface(offscreen);

    std::cout << SDL_GetError();
    
    // Update the surface
    SDL_UpdateWindowSurface(window);
    setFrameColor(0);
}

void Renderer::quit(){
    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}