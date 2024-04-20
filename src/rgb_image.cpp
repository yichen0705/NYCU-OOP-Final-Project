#include "rgb_image.h"

RGBImage::RGBImage(int w, int h, RGB_pixel **pixels) : Image(w, h){
    this->pixels = pixels;
}

RGBImage::~RGBImage(){
    for (int i = 0; i < h; ++i) {
        delete[] pixels[i];
    }
    delete[] pixels;
}