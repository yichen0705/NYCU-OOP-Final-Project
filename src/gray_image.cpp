#include "gray_image.h"

#include <cstdio>

GrayImage::GrayImage():Image(0, 0), pixels(nullptr) {}

GrayImage::GrayImage(int width, int height, int **pixels):Image(width, height){
    this->pixels = pixels;
}

GrayImage::~GrayImage(){
    if (pixels == nullptr){
        return;
    }

    for(int i=0; i < height; i++){
        delete []pixels[i];
    }
    delete []pixels;
}

bool GrayImage::LoadImage(string filename){
    pixels = data_loader.Load_Gray(filename, &width, &height);
    if(pixels == nullptr){
        cout<<"error loading image: "<<filename<<endl;
        return false;
    }
    return true;
}

void GrayImage::DumpImage(string filename){
    if (pixels==nullptr){
        return;
    }
    data_loader.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::Display_X_Server(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::Display_ASCII(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::Display_CMD(){
    if (pixels==nullptr){
        return;
    }
    data_loader.Dump_Gray(width, height, pixels, "temp.jpg");
    data_loader.Display_Gray_CMD("temp.jpg");
    remove("temp.jpg");
}
