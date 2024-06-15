#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image {
public:
    RGBImage() = default;
    RGBImage(int width, int height) : Image(width, height) {}
    virtual bool LoadImage(std::string filename);
    virtual Image* Copy();
};

#endif