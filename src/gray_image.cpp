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
    pixels = nullptr;
    pixels = data_loader.Load_Gray(filename, &w, &h);
    // data_loader.Display_Gray(w, h, pixels);
    data_loader.Display_Gray_ASCII(w, h, pixels);
    return true;
}

void GrayImage::DumpImage(string filename){
    data_loader.Dump_Gray(w, h, pixels, filename);
}

void GrayImage::Display_X_Server(){
    data_loader.Display_Gray_X_Server(w, h, pixels);
}

void GrayImage::Display_ASCII(){
    data_loader.Display_Gray_ASCII(w, h, pixels);
}

void GrayImage::Display_CMD(){
    data_loader.Dump_Gray(w, h, pixels, string("tmp.jpg"));
    data_loader.Display_Gray_CMD(string("tmp.jpg"));
    system("rm tmp.jpg");
}