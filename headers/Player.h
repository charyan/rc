#ifndef PLAYER_H
#define PLAYER_H

#include "Rect.h"

class Player{
    public:
        float angle;
        float x;
        float y;
        void setX(float _x);
        void setY(float _y);
        int getX();
        int getY();
        Rect r;
        Player();
        Player(float _angle, Rect _r);
};

#endif // PLAYER_H