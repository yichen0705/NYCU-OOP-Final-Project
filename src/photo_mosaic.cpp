#include "photo_mosaic.h"

#include <cstdint>
#include <vector>
#include <algorithm>

#include "image_loader.h"
#include "rgb_image.h"

static Color GetAverageColor(Color** pixels, int width, int height, int offset_x, int offset_y) {
    uint64_t total_r = 0;
    uint64_t total_g = 0;
    uint64_t total_b = 0;
    
    int total_pixels = width * height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color& pixel = pixels[y + offset_y][x + offset_x];
            total_r += pixel.r;
            total_g += pixel.g;
            total_b += pixel.b;
        }
    }

    Color result;
    result.r = (int)(total_r / total_pixels);
    result.g = (int)(total_g / total_pixels);
    result.b = (int)(total_b / total_pixels);

    return result; 
}

static uint64_t GetColorDistance(Color a, Color b) {
    uint64_t dr = a.r - b.r;
    uint64_t dg = a.g - b.g;
    uint64_t db = a.b - b.b;

    return dr * dr + dg * dg + db * db;
}

struct ImageColorPair {
    Image* image;
    Color avg_color;
};

Image* PhotoMosaic::Create(Image* target, std::string images_dir) {
    const int grid_size = SUB_IMAGE_SIZE;
    
    ImageLoader& loader = ImageLoader::GetInstance();

    std::vector<std::string> filenames;
    if (!loader.ListDirectory(images_dir, filenames)) {
        return nullptr;
    }

    std::vector<ImageColorPair> images;
    for(const auto& filename : filenames) {
        Image* image = new RGBImage();
        if (!image->LoadImage(filename)) {
            return nullptr;
        }
    
        ImageColorPair pair;
        pair.image = image;
        pair.avg_color = GetAverageColor(image->pixels, image->width, image->height, 0, 0);
        images.push_back(pair);
    }

    RGBImage* result = new RGBImage(target->width, target->height);
    if (result == nullptr || result->pixels == nullptr) {
        return nullptr;
    }

    for (int y = 0; y < target->height; y += grid_size) {
        for (int x = 0; x < target->width; x += grid_size) {
            int grid_width = std::min(target->width - x, grid_size);
            int grid_height = std::min(target->height - y, grid_size);

            Color grid_color = GetAverageColor(target->pixels, grid_width, grid_height, x, y);
        
            Image* best_image = images[0].image;
            uint64_t min_dist = UINT64_MAX;

            for (const auto& image : images) {
                uint64_t dist = GetColorDistance(image.avg_color, grid_color);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_image = image.image; 
                }
            }

            for (int by = 0; by < grid_height; by++) {
                for (int bx = 0; bx < grid_width; bx++) {
                    result->pixels[y + by][x + bx] = best_image->pixels[by][bx];
                }
            }
        }
    }

    for (auto& image : images) {
        delete image.image;
    }

    return result;
}
