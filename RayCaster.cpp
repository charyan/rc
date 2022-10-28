#include "headers/RayCaster.h"


void RayCaster::castRay(Player player){

    int r = 0;
    float x = 0.;
    float y = 0.;

    // increase r until we find a wall
    for(; r<1000; r += 1){
        x = player.r.x + r*cos(player.angle);
        y = player.r.y - r*sin(player.angle);
        
        bool quit = false;

        if(int(x) < 0){
            x = 0;
            quit = true;
        } else if (int(x) > rend->winW){
            x = rend->winW;
            quit = true;
        }

        if(int(y) < 0) {
            y = 0;
            quit = true;
        } else if (int(y) > rend->winH){
            y = rend->winH;
            quit = true;
        }


        if(rend->frame[int(x)+int(y)*rend->winW] == 0x7887fa) break;
        if(quit) break;
    }

    
    // draw the line between player and the hit point
    rend->plotLine(player.r.x, player.r.y, int(x), int(y));
    

    rend->drawRectToFrame(Rect(int(x), int(y), 10,10,0xFF0000));

    // rend->plotLine(int(x), 0, int(x), int(y));
    // rend->plotLine(0, int(y), int(x), int(y));

}

RayCaster::RayCaster(Renderer &_rend){
    rend = &_rend;
}

void RayCaster::applyGamemap(uint32_t* map, uint32_t _mapW, uint32_t _mapH){
    for(int y=0; y<_mapH; y++){
        for(int x=0; x<_mapW; x++){
            if(map[x+y*_mapW]==1){
                rend->drawRectToFrame(Rect(x*(rend->winW/_mapW),y*(rend->winH/_mapH),rend->winW/_mapW, rend->winH/_mapH, 0x7887fa));
            }
        }
    }



}