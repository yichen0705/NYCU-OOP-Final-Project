#include "rgb_image.h"

#include <cstdio>

RGBImage::RGBImage():Image(0, 0), pixels(nullptr) {}

RGBImage::RGBImage(int width, int height, int **pixels):Image(width, height), pixels(nullptr){}

RGBImage::~RGBImage(){
    if (pixels == nullptr){
        return;
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            delete []pixels[i][j];
        }
    }
    for(int i=0; i < height; i++){
        delete []pixels[i];
    }
    delete []pixels;
}

bool RGBImage::LoadImage(string filename){
    pixels = data_loader.Load_RGB(filename, &width, &height);
    if(pixels == nullptr){
        cout<<"error loading image: "<<filename<<endl;
        return false;
    }
    return true;
}

void RGBImage::DumpImage(string filename){
    if (pixels==nullptr){
        return;
    }
    data_loader.Dump_RGB(width, height, pixels, filename);
}

void RGBImage::Display_X_Server(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Display_RGB_X_Server(width, height, pixels);
}

void RGBImage::Display_ASCII(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Display_RGB_ASCII(width, height, pixels);
}

void RGBImage::Display_CMD(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Dump_RGB(width, height, pixels, "temp.jpg");
    data_loader.Display_RGB_CMD("temp.jpg");
    remove("temp.jpg");
}
