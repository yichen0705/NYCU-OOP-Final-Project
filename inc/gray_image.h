#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;
public:
    GrayImage();
    GrayImage(int width, int height, int **pixels);
    virtual~GrayImage();
    virtual bool LoadImage(string filename);
    virtual void DumpImage(string filename);
    virtual void Display_X_Server();
    virtual void Display_ASCII();
    virtual void Display_CMD();
};

#endif