#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image {
public:
    virtual bool LoadImage(std::string filename);
};

#endif