#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <SDL2/SDL.h>
#include "Player.h"


class Renderer{
    public:
        uint32_t* frame;
        uint32_t winW;
        uint32_t winH;

        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Surface* offscreen;

        void plotLineHigh(int x0, int y0, int x1, int y1);
        void plotLineLow(int x0, int y0, int x1, int y1);
        void plotLine(int x0, int y0, int x1, int y1);
        void setFrameColor(uint32_t _rgb);
        void drawRectToFrame(Rect rec);

        void updateWindow();
        void quit();

        Renderer(uint32_t _winW, uint32_t _winH);

};


#endif // RENDERER_H