#include "gray_image.h"

#include <cstdio>

#include "image_loader.h"

bool GrayImage::LoadImage(std::string filename){
    ImageLoader& loader = ImageLoader::GetInstance();
    pixels = loader.LoadImage(filename, width, height, true);
    if (pixels == nullptr) {
        std::cout << "error loading image: " << filename << std::endl;
        return false;
    }
    return true;
}
