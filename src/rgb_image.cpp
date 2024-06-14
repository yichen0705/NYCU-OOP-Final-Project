#include "rgb_image.h"

#include "image_loader.h"

bool RGBImage::LoadImage(std::string filename){
    ImageLoader& loader = ImageLoader::GetInstance();
    pixels = loader.LoadImage(filename, width, height, false);
    if (pixels == nullptr) {
        std::cout << "error loading image: " << filename << std::endl;
        return false;
    }
    return true;
}
