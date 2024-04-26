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
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

    // for photo mosaic
    double operator-(const RGBImage &obj);
    void GridAverage(int row, int col, int size);
    friend class PhotoMosaic;
};

#endif