#ifndef _DATA_LOADER_H_
#define _DATA_LOADER_H_

#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cimg_library;

class Data_Loader{
private:
    int ***rgb_pixels;
    int **pixels;

public:
    Data_Loader();
    ~Data_Loader();
    
    void Load_Gray(string filename, int *w, int *h, int **pixels);
    void Load_RGB(string filename, int *w, int *h, int ***pixels);
};

#endif