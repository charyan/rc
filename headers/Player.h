#ifndef PLAYER_H
#define PLAYER_H

#include "Rect.h"

class Player{
    public:
        float angle;
        Rect r;
        Player();
        Player(float _angle, Rect _r);
};

#endif // PLAYER_H