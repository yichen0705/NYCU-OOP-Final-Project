#include "image_filter.h"

class InvertFilter : public ImageFilter {
public:
    InvertFilter() : ImageFilter(FILTER_INVERT) {}
    virtual void Apply(Image* image) const;
};

static InvertFilter invert_filter;

void InvertFilter::Apply(Image* image) const {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            Color& color = image->pixels[i][j];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;
        }
    }
}
