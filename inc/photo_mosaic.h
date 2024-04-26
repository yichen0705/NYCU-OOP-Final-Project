#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#define SUB_PIC_SIZE 32
#include "rgb_image.h"

class PhotoMosaic{
private:
    static Data_Loader data_loader;
    
    RGBImage target_img;
    vector<string> candidate_filenames;

public:
    PhotoMosaic();
    ~PhotoMosaic();
    RGBImage* run(string targetPath, string candidatePath);
};

#endif