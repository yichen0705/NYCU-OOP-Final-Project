#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
    int ***pixels;
    double r_avg;
    double g_avg;
    double b_avg;

public:
    RGBImage();
    RGBImage(int w, int h, int ***pixels);
    ~RGBImage();
    bool LoadImage(string filename);
    double operator- (RGBImage &rhs);
    // bool operator< (RGBImage &rhs);
    void calAverage(int row, int col);
    friend class PhotoMosaic;
};

#endif