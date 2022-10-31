#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "Player.h"


class Renderer{
    public:
        uint32_t* frame;
        uint32_t* rcView;
        uint32_t* windowFrame;
        uint32_t winW;
        uint32_t winH;

        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Surface* offscreen;

        void plotLine(int x0, int y0, int x1, int y1);
        void setFrameColor(uint32_t _rgb);
        void drawRectToFrame(Rect rec);
        void saveFrameToFile();
        void updateWindow();
        void quit();
        void stitchViews();

        Renderer(uint32_t _winW, uint32_t _winH);

    private:
        void plotLineHigh(int x0, int y0, int x1, int y1);
        void plotLineLow(int x0, int y0, int x1, int y1);


};


#endif // RENDERER_H