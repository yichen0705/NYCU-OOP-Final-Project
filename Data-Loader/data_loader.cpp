#include "data_loader.h"

Data_Loader::Data_Loader(){
    ;
}

// Assume user will free the image
Data_Loader::~Data_Loader(){
    ;
}

int **Data_Loader::Load_Gray(string filename, int *w, int *h){
    CImg<unsigned char> img(filename.c_str());

    int _w = img.width();
    int _h = img.height();
    int _c = img.spectrum();

    *w = _w;
    *h = _h;

    // allocate memory for the image array
    pixels = new int *[_h];
    for(int i = 0; i < _h; i++){
        pixels[i] = new int[_w];
    }

    if(_c == 1){
        // macro to loop through the img
        cimg_forXY(img, x, y){
            pixels[y][x] = (int)img(x,y);
        }
        return pixels;
    }
    
    // rgb img -> convert it into gray scale img
    CImg<unsigned char> grayscale_img(_w, _h, 1);
    cimg_forXY(grayscale_img, x, y){
        grayscale_img(x, y) = (unsigned char)(R_FACTOR * img(x, y, 0, 0) + G_FACTOR * img(x, y, 0, 1) + B_FACTOR * img(x, y, 0, 2));
    }
    cimg_forXY(img, x, y){
        pixels[y][x] = (int)grayscale_img(x,y);
    }
    return pixels;

    // for(int i=0;i<_h;i++){
    //    for(int j=0;j<_w;j++){
    //       if(pixels[i][j] > 127){
    //         cout << "@@";
    //       }
    //       else cout << "__";
    //    }
    //    cout << endl;
    // }

    // Display the loaded image
    // CImgDisplay disp(grayscale_img, "Loaded Image");
    // while (!disp.is_closed()) {
    //     disp.wait();
    // }
}

int ***Data_Loader::Load_RGB(string filename, int *w, int *h){

    return nullptr;
}