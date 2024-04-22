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
    if(pixels == nullptr) return false;
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

double RGBImage::operator- (RGBImage &rhs){
    double r_diff = r_avg-rhs.r_avg;
    double g_diff = g_avg-rhs.g_avg;
    double b_diff = b_avg-rhs.b_avg;
    return sqrt(r_diff*r_diff + g_diff*g_diff + b_diff*b_diff);
}

// bool RGBImage::operator< (RGBImage &rhs){
//     return diff < rhs.diff;
// }

void RGBImage::calAverage(int row, int col){
    for(int i = row; i < row+32; i++){
        for(int j = col; j < col+32; j++){
            r_avg += pixels[i][j][0];
            g_avg += pixels[i][j][1];
            b_avg += pixels[i][j][2];
        }
    }
    r_avg /= h * w;
    g_avg /= h * w;
    b_avg /= h * w;
}