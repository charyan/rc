#ifndef RECT_H
#define RECT_H

#include <iostream>

class Rect
{
    public:
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
        uint32_t color;
        
        void setX(uint32_t _x);

        void setY(uint32_t _y);

        void setWidth(uint32_t _width);

        void setHeight(uint32_t _height);

        void setColor(uint32_t _color);

        Rect(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, uint32_t _color);
        Rect();
};






#endif // RECT_H
