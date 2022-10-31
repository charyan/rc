#include "headers/Player.h"


Player::Player(){
    angle = 0;
    r = Rect();
    x = r.x;
    y = r.y;
}
Player::Player(float _angle, Rect _r){
    angle = _angle;
    r = _r;
    x = r.x;
    y = r.y;
}

void Player::setX(float _x){
    x = _x;
}

void Player::setY(float _y){
    y = _y;
}


int Player::getX(){return (int)x;}
int Player::getY(){return (int)y;}
