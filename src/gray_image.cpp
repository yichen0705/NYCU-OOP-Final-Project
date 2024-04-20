#include "gray_image.h"

GrayImage::GrayImage() : Image(0, 0){
    ;
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

void GrayImage::LoadImage(string filename){
    CImg<unsigned char> image(filename.c_str()), visu(500,400,1,3,0); 
}