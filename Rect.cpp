#include "headers/Rect.h"



void Rect::setX(uint32_t _x){
    x = _x;
}

void Rect::setY(uint32_t _y){
    y = _y;
}

void Rect::setWidth(uint32_t _width){
    width = _width;
}

void Rect::setHeight(uint32_t _height){
    height = _height;
}

void Rect::setColor(uint32_t _color){
    color = _color;
}

Rect::Rect(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, uint32_t _color){
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
}

Rect::Rect(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->color = 0xFFFFFF;
}