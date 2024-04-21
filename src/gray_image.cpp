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
    int **pixels = nullptr;
    Data_Loader data_loader;
    pixels = data_loader.Load_Gray(filename, &w, &h);

    for(int i=0;i<h;i++){
       for(int j=0;j<w;j++){
          if(pixels[i][j] > 127){
            cout << "@@";
          }
          else cout << "__";
       }
       cout << endl;
    }
}