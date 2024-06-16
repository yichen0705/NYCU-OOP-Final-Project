#ifndef IMAGE_FILTER_MANAGER
#define IMAGE_FILTER_MANAGER

#include <cstdint>
#include <vector>

#include "image.h"

class ImageFilter;

class ImageFilterManager {
public:
    static ImageFilterManager& GetInstance() {
        static ImageFilterManager instance;
        return instance;
    }

    void ApplyFilters(Image* image, uint32_t options);

private:
    ImageFilterManager() = default;
    void AddFilter(ImageFilter* filter);
    std::vector<ImageFilter*> filters;

public:
    ImageFilterManager(ImageFilterManager const&) = delete;
    void operator=(ImageFilterManager const&) = delete;

    friend class ImageFilter;
};

#endif
