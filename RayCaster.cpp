#include "headers/RayCaster.h"

uint32_t RayCaster::packRGB(uint8_t _r, uint8_t _g, uint8_t _b){
    uint32_t _rgb = 0;

    _rgb   = _r;
    _rgb <<=  8;
    _rgb  |= _g;
    _rgb <<=  8;
    _rgb  |= _b;
    return _rgb;
}

void RayCaster::drawRayCastView(Player player){
    int sliceWidth = 10; // in px

    uint32_t* view = rend->rcView;
    float angleStep = (3.14/2)/(rend->winW)*sliceWidth;

    float modifier = 0xFF/sqrt(pow(rend->winH,2)+pow(rend->winW,2));

    int slice = 0;
    for(float i=player.angle+(3.14/4); i>player.angle-(3.14/4); i-=angleStep){
        float d = castRay(player, i);
        if(d != -1){
            float height = (rend->winH)/d;
            height *= 60;

            int c = 0xFF-d*modifier;
            int color = packRGB(c,c,c);
            height = (height > rend->winH) ? rend->winH : height;
            rend->drawRectToFrame(Rect(slice*sliceWidth,rend->winH/2-height/2,sliceWidth,height,color), view);
        }
        slice++;
    }

    // castRay(player, player.angle-(3.14/4));
    // castRay(player, player.angle+(3.14/4));
}

float RayCaster::castRay(Player player){
    return castRay(player, player.angle);
}
float RayCaster::castRay(Player player, float angle){

    float r = 0;
    float x = 0.;
    float y = 0.;

    bool quit = false;
    // increase r until we find a wall
    while(true){
        r += 1;
        x = player.x + r*cos(angle);
        y = player.y - r*sin(angle);
        

        if(x < 0){
            x = 0;
            quit = true;
        } else if (x > rend->winW){
            x = rend->winW;
            quit = true;
        }

        if(y < 0) {
            y = 0;
            quit = true;
        } else if (y > rend->winH){
            y = rend->winH;
            quit = true;
        }


        if(rend->frame[int(x)+int(y)*rend->winW] == 0x7887fa) break;
        if(quit) break;
    }

    
    // draw the line between player and the hit point
    rend->plotLine(player.getX(), player.getY(), int(x), int(y));
    

    // rend->drawRectToFrame(Rect(int(x), int(y), 10,10,0xFF0000));

    // rend->plotLine(int(x), 0, int(x), int(y));
    // rend->plotLine(0, int(y), int(x), int(y));
    return (quit) ? -1 : sqrt(pow(r*cos(angle),2) + pow(r*sin(angle),2));
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