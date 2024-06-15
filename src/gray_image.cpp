#include "gray_image.h"

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

Image* GrayImage::Copy() {
    GrayImage* copy = new GrayImage(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy->pixels[i][j] = pixels[i][j];
        }
    }

    return copy;
}
