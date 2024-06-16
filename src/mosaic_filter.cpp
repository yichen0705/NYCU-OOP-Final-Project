#include "image_filter.h"

class MosaicFilter : public ImageFilter {
public:
    MosaicFilter() : ImageFilter(FILTER_MOSAIC) {}
    virtual void Apply(Image* image) const;
};

static MosaicFilter mosaic_filter;

void MosaicFilter::Apply(Image* image) const {
    const int block_size = 32;

    for (int y = 0; y < image->height; y += block_size) {
        for (int x = 0; x < image->width; x += block_size) {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;

            int count = 0;

            for (int by = 0; by < block_size; by++) {
                for (int bx = 0; bx < block_size; bx++) {
                    int ny = y + by;
                    int nx = x + bx;

                    if (ny < image->height && nx < image->width) {
                        Color& color = image->pixels[ny][nx];
                        sum_r += color.r;
                        sum_g += color.g;
                        sum_b += color.b;
                        count++;
                    }
                }
            }

            int avg_r = sum_r / count;
            int avg_g = sum_g / count;
            int avg_b = sum_b / count;

            for (int by = 0; by < block_size; by++) {
                for (int bx = 0; bx < block_size; bx++) {
                    int ny = y + by;
                    int nx = x + bx;

                    if (ny < image->height && nx < image->width) {
                        image->pixels[ny][nx].r = avg_r;
                        image->pixels[ny][nx].g = avg_g;
                        image->pixels[ny][nx].b = avg_b;
                    }
                }
            }
        }
    }
}
