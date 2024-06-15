#include <iostream>

#include "image.h"
#include "rgb_image.h"
#include "image_filter.h"

struct FilterPair {
    const char* name;
    FilterType type;
};

FilterPair filters[] = {
    {"blur", FILTER_BLUR},
    {"invert", FILTER_INVERT},
    {"mosaic", FILTER_MOSAIC},
    {"edge", FILTER_EDGE},
    {"swirl", FILTER_SWIRL},
};

int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    Image *img = new RGBImage();
    if (!img->LoadImage(argv[1])) {
        std::cout << "Failed to load image\n";
        return 1;
    }

    ImageFilterManager& mgr = ImageFilterManager::GetInstance();
    
    uint32_t options = 0;
    for (const auto& filter : filters) {
        char c;
        std::cout << "Apply filter " << filter.name << "? (Y/n) ";
        std::cin >> c;
        if (c == 'Y' || c == 'y') {
            options |= filter.type;
        }
    }

    mgr.ApplyFilters(img, options);

    img->Display_X_Server();

    delete img;

    return 0;
}
