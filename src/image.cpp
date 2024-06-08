#include "image.h"

Image::Image(int _width, int _height) : width(_width), height(_height){

}

Image::~Image(){

}

int Image::get_width(){
    return width;
}

int Image::get_height() {
    return height;
}