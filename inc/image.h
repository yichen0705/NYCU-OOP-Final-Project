#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"

using namespace std;

class Image{
protected:
    int width;
    int height;
    Data_Loader data_loader;
public:
    Image(int _width, int _height);
    virtual~Image();
    virtual bool LoadImage(string filename) = 0;
    virtual void DumpImage(string filename) = 0;
    virtual void Display_X_Server() = 0;
    virtual void Display_ASCII() = 0;
    virtual void Display_CMD() = 0;
    int get_width();
    int get_height();
};

#endif