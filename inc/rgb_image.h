#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"
#include "rgb_pixel.h"
#include "gray_image.h"

class RGBImage : public Image{
private:
    RGB_pixel **pixels;

public:
    RGBImage(int w, int h, RGB_pixel **pixels);
    ~RGBImage();
};

#endif