#include "headers/Player.h"


Player::Player(){
    angle = 0;
    r = Rect();
}
Player::Player(float _angle, Rect _r){
    angle = _angle;
    r = _r;
}
