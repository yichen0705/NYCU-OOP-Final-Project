#include "image_filter.h"

#include <cmath>
#include <algorithm>

class EdgeFilter : public ImageFilter {
public:
    EdgeFilter() : ImageFilter(FILTER_EDGE) {}
    virtual void Apply(Image* image) const;
};

static EdgeFilter edge_filter;

void EdgeFilter::Apply(Image* image) const {
    Image* copy = image->Copy();

    const int gx[3][3] = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1},
    };

    const int gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1},
    };

    for (int y = 1; y < image->height - 1; y++) {
        for (int x = 1; x < image->width - 1; x++) {
            int sum_xr = 0;
            int sum_xg = 0;
            int sum_xb = 0;
            int sum_yr = 0;
            int sum_yg = 0;
            int sum_yb = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    Color& color = copy->pixels[y + ky][x + kx];
                    sum_xr += gx[ky + 1][kx + 1] * color.r;
                    sum_xg += gx[ky + 1][kx + 1] * color.g;
                    sum_xb += gx[ky + 1][kx + 1] * color.b;
                    sum_yr += gy[ky + 1][kx + 1] * color.r;
                    sum_yg += gy[ky + 1][kx + 1] * color.g;
                    sum_yb += gy[ky + 1][kx + 1] * color.b;
                }
            }

            int mag_r = std::sqrt(sum_xr * sum_xr + sum_yr * sum_yr);
            int mag_g = std::sqrt(sum_xg * sum_xg + sum_yg * sum_yg);
            int mag_b = std::sqrt(sum_xb * sum_xb + sum_yb * sum_yb);

            image->pixels[y][x].r = std::min(255, mag_r);
            image->pixels[y][x].g = std::min(255, mag_g);
            image->pixels[y][x].b = std::min(255, mag_b);
        }
    }

    delete copy;
}
