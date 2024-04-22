#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string.h>
#include "data_loader.h"

using namespace std;

class Image{
protected:
    int w;
    int h;
    static Data_Loader data_loader;

public:
    Image(int w, int h);
    virtual ~Image();
    virtual bool LoadImage(string filename) = 0;
    virtual void DumpImage(string filename) = 0;
    virtual void Display_X_Server() = 0;
    virtual void Display_ASCII() = 0;
    virtual void Display_CMD() = 0;
    int get_w();
    int get_h();
    
};

#endif

