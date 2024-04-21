#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string.h>
#include <data_loader.h>

using namespace std;

class Image{
protected:
    int w;
    int h;
    static Data_Loader data_loader;

public:
    Image(int w, int h);
    virtual ~Image();
    virtual void LoadImage(string filename) = 0;
};

#endif