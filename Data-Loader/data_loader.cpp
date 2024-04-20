#include "data_loader.h"

Data_Loader::Data_Loader(){
    ;
}

// Assume user will free the image
Data_Loader::~Data_Loader(){
    ;
}

void Data_Loader::Load_Gray(string filename, int *w, int *h, int **pixels){
    CImg<unsigned char> img(filename.c_str());

    // Get width, height, number of channels
    int _w=img.width();
    int _h=img.height();
    int _c=img.spectrum();
    cout << "Dimensions: " << _w << "x" << _h << " " << _c << " channels" <<endl;

    // Dump all pixels
    for(int y=0;y<_h;y++){
       for(int x=0;x<_w;x++){
          cout << y << "," << x << " " << (int)img(x,y) << endl;
       }
    }

    for(int y=0;y<_h;y++){
       for(int x=0;x<_w;x++){
          if(img(x,y) > 127){
            cout << "@@";
          }
          else cout << "__";
       }
       cout << endl;
    }

    // Display the loaded image
    CImgDisplay disp(img, "Loaded Image");
    while (!disp.is_closed()) {
        disp.wait();
    }
}

void Data_Loader::Load_RGB(string filename, int *w, int *h, int ***pixels){

}