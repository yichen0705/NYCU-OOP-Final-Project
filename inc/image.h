#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdint>
#include <vector>
#include <string>

#include "color.h"

class BlurFilter;
class InvertFilter;
class MosaicFilter;
class EdgeFilter;
class SwirlFilter;

class PhotoMosaic;

class Image {
public:
    Image()=default;
    Image(int width, int height);
    virtual ~Image();
    
    virtual bool LoadImage(std::string filename) = 0;
;   void DumpImage(std::string filename);
    
    virtual Image* Copy() = 0;
    
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    friend class BlurFilter;
    friend class InvertFilter;
    friend class MosaicFilter;
    friend class EdgeFilter;
    friend class SwirlFilter;

    friend class PhotoMosaic;

protected:
    int width = 0;
    int height = 0;
    Color** pixels = nullptr;
};

#endif