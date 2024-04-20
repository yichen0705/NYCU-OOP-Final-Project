#include "data_loader.h"

Data_Loader::Data_Loader(){
    ;
}

// Assume user will free the image
Data_Loader::~Data_Loader(){
    ;
}

void Data_Loader::Load_Gray(string filename, int *w, int *h, int **pixels){
    CImg<unsigned char> image(filename.c_str());

    // Get image dimensions
    *w = image.width();
    *h = image.height();

    // Allocate memory for 2D array
    pixels = new int *[image.height()];
    for (int i = 0; i < image.height(); ++i) {
        pixels[i] = new int[image.width()];
    }

    cimg_forXY(image, x, y) {
        pixels[y][x] = image(x, y, 0, 0);
    }

    // Display the loaded image
    CImgDisplay disp(image, "Loaded Image");
    while (!disp.is_closed()) {
        disp.wait();
    }
}

void Data_Loader::Load_RGB(string filename, int *w, int *h, int ***pixels){

}