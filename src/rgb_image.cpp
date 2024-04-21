#include "rgb_image.h"

// Initialize the static Data_Loader object
Data_Loader RGBImage::data_loader(0);

RGBImage::RGBImage() : Image(0, 0){
    pixels = nullptr;
}

RGBImage::RGBImage(int w, int h, RGB_pixel **pixels) : Image(w, h){
    this->pixels = pixels;
}

RGBImage::~RGBImage(){
    for (int i = 0; i < h; ++i) {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void RGBImage::LoadImage(string filename){
    int ***pixels = nullptr;
    pixels = data_loader.Load_RGB(filename, &w, &h);
    data_loader.Display_RGB(w, h, pixels);
    data_loader.Display_RGB_ASCII(w, h, pixels);
}