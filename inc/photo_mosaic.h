#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include <string>

#include "image.h"

#define SUB_IMAGE_SIZE 32

class PhotoMosaic{
public:
    static Image* Create(Image* target, std::string images_dir);
};

#endif