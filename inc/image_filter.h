#ifndef BIT_FIELD_FILTER
#define BIT_FIELD_FILTER

#include <cstdint>

#include "image.h"

class ImageFilter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~ImageFilter() = default;
};

#endif
