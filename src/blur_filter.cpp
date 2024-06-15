#include "image_filter.h"

class BlurFilter : public ImageFilter {
public:
    BlurFilter() : ImageFilter(FILTER_BLUR) {}
    virtual void Apply(Image* image) const;
};

static BlurFilter blur_filter;

void BlurFilter::Apply(Image* image) const {
    Image* copy = image->Copy();

    const int kernal = 5;
    const int offset = kernal / 2;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            
            int count = 0;
            
            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    int ny = y + ky;
                    int nx = x + kx;

                    if (ny >= 0 && ny < image->height && nx >= 0 && nx < image->width) {
                        Color color = copy->pixels[ny][nx];
                        sum_r += color.r;
                        sum_g += color.g;
                        sum_b += color.b;
                        count++;
                    }
                }
            }
            image->pixels[y][x].r = sum_r / count;
            image->pixels[y][x].g = sum_g / count;
            image->pixels[y][x].b = sum_b / count;
        }
    }

    delete copy;
}
