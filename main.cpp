#include <iostream>
#include <fstream>
#include <vector>

#include <ctime>
#include <cstdlib>


const unsigned int WIN_H = 1000;
const unsigned int WIN_W = 1000;

const unsigned int TILE_SIZE = 100;

uint32_t packRGB(uint8_t _r, uint8_t _g, uint8_t _b){
    uint32_t _rgb = 0;

    _rgb   = _r;
    _rgb <<=  8;
    _rgb  |= _g;
    _rgb <<=  8;
    _rgb  |= _b;
    return _rgb;
}

void bitPrint(uint32_t a) {
     for(int i=UINT32_WIDTH; i>0; i--) {
        if(i%4==0){
            printf(" ");
        }
         printf("%d", (a>>i-1)&1);   
         }
        
        printf("\n");
    }


int main()
{
    uint32_t frame[WIN_W][WIN_H] = {};
    std::srand(std::time(nullptr));
    uint32_t color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
    
    for(int y=0; y<WIN_H; y++){
        for(int x=0; x<WIN_H; x++){
            if(x%TILE_SIZE==0 && y%TILE_SIZE==0){
                color = packRGB(std::rand()%255, std::rand()%255, std::rand()%255);
                frame[x][y] = color;
            } else{
                if(y%TILE_SIZE!=0){
                    frame[x][y] = frame[x][y-1];
                }
                if(x%TILE_SIZE!=0){
                    frame[x][y] = frame[x-1][y];
                }
            }
        }
    }

    



    std::ofstream File("frame.ppm", std::ios::out | std::ios::binary);

    File << "P6" << (uint8_t)0x0A << WIN_W << (uint8_t)0x20 << WIN_H << (uint8_t)0x0A << "255" << (uint8_t)0x0A;
    
    for(int y=0; y<WIN_H; y++){
        for(int x=0; x<WIN_W; x++){
            // R
            File << (uint8_t)(frame[x][y]>>16);
            // G
            File << (uint8_t)((frame[x][y]>>8)&0x000000FF);
            // B
            File << (uint8_t)(frame[x][y]&0x000000FF);
        }
    }
    
    File.close();

    return 0;
}