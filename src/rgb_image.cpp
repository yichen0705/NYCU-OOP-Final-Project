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

Image* RGBImage::Copy() {
    RGBImage* copy = new RGBImage(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy->pixels[i][j] = pixels[i][j];
        }
    }

    return copy;
}
