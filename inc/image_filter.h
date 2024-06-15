#ifndef IMAGE_FILTER
#define IMAGE_FILTER

#include <cstdint>

#include "image.h"
#include "image_filter_manager.h"

enum FilterType : uint32_t {
    FILTER_NONE = 0,
    FILTER_BLUR = 1 << 0,
    FILTER_INVERT = 1 << 1,
    FILTER_MOSAIC = 1 << 2,
};

class ImageFilter {
public:
    ImageFilter(FilterType flag) : _flag(flag) {
        ImageFilterManager& mgr = ImageFilterManager::GetInstance();
        mgr.AddFilter(this);
    }

    virtual ~ImageFilter() = default;
    virtual void Apply(Image* image) const = 0;
    virtual bool ShouldApply(uint32_t options) const {
        return options & _flag;
    }

private:
    FilterType _flag = FILTER_NONE;
};

#endif
