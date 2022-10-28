#include "headers/RayCaster.h"


void RayCaster::castRay(Player player){

    float x = player.r.x + 150*cos(player.angle);
    float y = player.r.y - 150*sin(player.angle);
    
    rend->plotLine(player.r.x, player.r.y, int(x), int(y));

    // r.plotLine(int(x), 0, int(x), int(y));
    // r.plotLine(0, int(y), int(x), int(y));

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