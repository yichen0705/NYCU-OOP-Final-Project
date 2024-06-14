#include "image_filter_manager.h"

#include "image_filter.h"

void ImageFilterManager::ApplyFilters(Image* image, uint32_t options) {
    for (const auto* filter : filters) {
        if (filter->ShouldApply(options)) {
            filter->Apply(image);
        }
    }
}

void ImageFilterManager::AddFilter(ImageFilter* filter) {
    filters.push_back(filter);
}
