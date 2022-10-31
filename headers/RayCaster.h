#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "Player.h"
#include "Rect.h"
#include "Renderer.h"

class RayCaster{
    public:
        float castRay(Player player);
        float castRay(Player player, float angle);
        void applyGamemap(uint32_t* map, uint32_t _mapW, uint32_t _mapH);
        RayCaster(Renderer &_rend);
        void drawRayCastView(Player player);
        

    private:
        Renderer* rend;
        uint32_t packRGB(uint8_t _r, uint8_t _g, uint8_t _b);

};


#endif //RAYCASTER_H