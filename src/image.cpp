#include "image.h"

// Initialize the static Data_Loader object
Data_Loader Image::data_loader(0);

Image::Image(int w, int h){
    this->w = w;
    this->h = h;
}

Image::~Image(){
    ;
}