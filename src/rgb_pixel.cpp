#include "rgb_pixel.h"

RGB_pixel::RGB_pixel(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

RGB_pixel::RGB_pixel(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}

RGB_pixel::~RGB_pixel(){
    ;
}