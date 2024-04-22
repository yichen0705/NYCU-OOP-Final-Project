#ifndef PHOTO_MOSAIC
#define PHOTO_MOSAIC
#include "rgb_image.h"

class PhotoMosaic{
public:
    PhotoMosaic();
    ~PhotoMosaic();

    int*** run(string targetPath, string candidatePath);
private:
    Data_Loader data_loader;
    vector<RGBImage> candidates; // store all information of candidates
};

#endif