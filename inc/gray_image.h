#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image {
public:
    virtual bool LoadImage(std::string filename);
};

#endif