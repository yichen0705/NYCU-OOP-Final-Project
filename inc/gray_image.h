#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;

public:
    GrayImage();
    GrayImage(int w, int h, int **pixels);
    ~GrayImage();
    bool LoadImage(string filename);
};

#endif