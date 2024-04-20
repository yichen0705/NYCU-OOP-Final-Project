#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string.h>
#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

class Image{
protected:
    int w;
    int h;

public:
    Image(int w, int h);
    virtual ~Image();
    virtual void LoadImage(string filename) = 0;
};

#endif