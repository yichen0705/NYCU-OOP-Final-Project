#include "invert_filter.h"

static InvertFilter invert_filter;

void InvertFilter::Apply(Image* image) const {
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            Color& color = image->pixels[i][j];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;
        }
    }
}
