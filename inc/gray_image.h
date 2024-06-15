#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image {
public:
    GrayImage() = default;
    GrayImage(int width, int height) : Image(width, height) {}
    virtual bool LoadImage(std::string filename);
    virtual Image* Copy();
};

#endif