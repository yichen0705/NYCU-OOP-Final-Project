#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
public:
    int **pixels;

public:
    GrayImage();
    GrayImage(int w, int h, int **pixels);
    ~GrayImage();
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
};

#endif