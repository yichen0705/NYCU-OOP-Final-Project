#ifndef INVERT_FILTER
#define INVERT_FILTER

#include "image_filter.h"

class InvertFilter : public ImageFilter {
public:
    InvertFilter() : ImageFilter(FILTER_INVERT) {}
    virtual void Apply(Image* image) const;
};

#endif
