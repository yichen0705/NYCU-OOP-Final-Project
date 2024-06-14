#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdint>
#include <vector>
#include <string>

#include "color.h"


class InvertFilter;

class Image {
public:
    Image()=default;
    virtual ~Image();
    
    virtual bool LoadImage(std::string filename) = 0;
    void DumpImage(std::string filename);
    
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    friend class InvertFilter;    

protected:
    int width = 0;
    int height = 0;
    Color** pixels = nullptr;
};

#endif