#include "image.h"

// Initialize the static Data_Loader object
Data_Loader Image::data_loader;

Image::Image(int w, int h){
    this->w = w;
    this->h = h;
}

Image::~Image(){
    ;
}

int Image::get_w(){
    return w;
}

int Image::get_h(){
    return h;
}