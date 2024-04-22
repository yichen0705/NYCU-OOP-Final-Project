#ifndef _DATA_LOADER_H_
#define _DATA_LOADER_H_

#define cimg_use_jpeg
#include "CImg.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

// for luminance formula: Y = 0.2126R + 0.7152G + 0.0722B
#define R_FACTOR 0.2126
#define G_FACTOR 0.7152
#define B_FACTOR 0.0722

using namespace std;
using namespace cimg_library;

class Data_Loader{
private:
    int verbose = 0;
    int ***rgb_pixels;
    int **pixels;

public:
    Data_Loader();
    Data_Loader(int verbose);
    ~Data_Loader();
    void Set_Verbose(int verbose);
    int **Load_Gray(string filename, int *w, int *h);
    int ***Load_RGB(string filename, int *w, int *h);
    void Display_Gray(int w, int h, int **pixels);
    void Display_RGB(int w, int h, int ***pixels);
    void Display_Gray_ASCII(int w, int h, int **pixels);
    void Display_RGB_ASCII(int w, int h, int ***pixels);
    bool List_Directory(string directoryPath, vector<string> &filenames);
};

#endif