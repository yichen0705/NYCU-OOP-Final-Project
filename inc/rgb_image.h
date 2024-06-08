#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
    int ***pixels;
public:
    RGBImage();
    RGBImage(int width, int height, int **pixels);
    virtual~RGBImage();
    virtual bool LoadImage(string filename);
    virtual void DumpImage(string filename);
    virtual void Display_X_Server();
    virtual void Display_ASCII();
    virtual void Display_CMD();
};

#endif