#include "rgb_image.h"

RGBImage::RGBImage() : Image(0, 0), r_avg(0), g_avg(0), b_avg(0){
    pixels = nullptr;
}

RGBImage::RGBImage(int w, int h, int ***pixels) : Image(w, h){
    this->pixels = pixels;
}

RGBImage::~RGBImage(){
    for (int i = 0; i < h; ++i) {
        for(int j = 0; j < w; j++){
            delete[] pixels[i][j];
        }
    }
    for(int i = 0; i < h; i++){
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = nullptr;
}

bool RGBImage::LoadImage(string filename){
    pixels = data_loader.Load_RGB(filename, &w, &h);
    if(pixels == nullptr){
        cout << "Load error" << endl;
        return false;
    }
    // data_loader.Display_RGB(w, h, pixels);
    // data_loader.Display_RGB_ASCII(w, h, pixels);
    // calculate average of r, g, b, respectively
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            r_avg += pixels[i][j][0];
            g_avg += pixels[i][j][1];
            b_avg += pixels[i][j][2];
        }
    }
    r_avg /= w*h;
    g_avg /= w*h;
    b_avg /= w*h;
    return true;
}

void RGBImage::DumpImage(string filename){
    data_loader.Dump_RGB(w, h, pixels, filename);
}

void RGBImage::Display_X_Server(){
    data_loader.Display_RGB_X_Server(w, h, pixels);
}

void RGBImage::Display_ASCII(){
    data_loader.Display_RGB_ASCII(w, h, pixels);
}

void RGBImage::Display_CMD(){
    data_loader.Dump_RGB(w, h, pixels, string("tmp.jpg"));
    data_loader.Display_RGB_CMD(string("tmp.jpg"));
    system("rm tmp.jpg");
}


double RGBImage::operator-(const RGBImage &obj){
    double r_diff = r_avg - obj.r_avg;
    double g_diff = g_avg - obj.g_avg;
    double b_diff = b_avg - obj.b_avg;
    return sqrt(r_diff * r_diff + g_diff * g_diff + b_diff * b_diff);
}

void RGBImage::GridAverage(int row, int col, int size){
    for(int i = row; i < row+ size; i++){
        for(int j = col; j < col+ size; j++){
            r_avg += pixels[i][j][0];
            g_avg += pixels[i][j][1];
            b_avg += pixels[i][j][2];
        }
    }
    r_avg /= size * size;
    g_avg /= size * size;
    b_avg /= size * size;
}