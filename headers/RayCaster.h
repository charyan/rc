#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "Player.h"
#include "Rect.h"
#include "Renderer.h"

class RayCaster{
    public:
        void castRay(Player player);
        void applyGamemap(uint32_t* map, uint32_t _mapW, uint32_t _mapH);
        RayCaster(Renderer &_rend);
        

    private:
        Renderer* rend;

};


#endif //RAYCASTER_H