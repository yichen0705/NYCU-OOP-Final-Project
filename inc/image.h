#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string.h>
#include <data_loader.h>
#define q
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