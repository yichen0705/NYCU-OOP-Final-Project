#include "gray_image.h"

GrayImage::GrayImage() : Image(0, 0){
    pixels =  nullptr;
}

GrayImage::GrayImage(int w, int h, int **pixels) : Image(w, h){
    this->pixels = pixels;
}

GrayImage::~GrayImage(){
    for(int i = 0; i < h; ++i){
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = nullptr;
}

bool GrayImage::LoadImage(string filename){
    int **pixels = nullptr;
    pixels = data_loader.Load_Gray(filename, &w, &h);
    // data_loader.Display_Gray(w, h, pixels);
    data_loader.Display_Gray_ASCII(w, h, pixels);
    return true;
}