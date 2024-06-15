#include "image_filter.h"

#include <cmath>

class SwirlFilter : public ImageFilter {
public:
    SwirlFilter() : ImageFilter(FILTER_SWIRL) {}
    virtual void Apply(Image* image) const;
};

static SwirlFilter swirl_filter;

void SwirlFilter::Apply(Image* image) const {
    Image* copy = image->Copy();

    double strength = 10.0;

    double center_x = image->width / 2.0;
    double center_y = image->height / 2.0;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
           double offset_x = x - center_x;
           double offset_y = y - center_y;

           double radius = std::sqrt(offset_x * offset_x + offset_y * offset_y);
           double angle = std::atan2(offset_y, offset_x) + strength * radius / 1000.0;

           int new_x = (int)(center_x + radius * std::cos(angle));
           int new_y = (int)(center_y + radius * std::cos(angle));

           if (new_x >= 0 && new_x < image->width && new_y >= 0 && new_y < image->height) {
                image->pixels[y][x] = copy->pixels[new_y][new_x];
           }
        }
    }

    delete copy;
}
