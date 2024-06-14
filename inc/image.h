#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdint>
#include <vector>
#include <string>

#include "color.h"


class BaseFilter;

class Image {
public:
    enum FilterType {
        FILTER_BLUR = 1 << 0,
        FILTER_INVERT = 1 << 1,
    };

    Image()=default;
    virtual ~Image();
    
    virtual bool LoadImage(std::string filename) = 0;
    void DumpImage(std::string filename);
    
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

    void ApplyFilters(uint32_t options);

    int get_width() { return width; }
    int get_height() { return height; }

protected:
    int width = 0;
    int height = 0;
    Color** pixels = nullptr;
};

#endif