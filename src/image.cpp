#include "image.h"

#include "image_loader.h"

Image::~Image() {
    if (pixels == nullptr) {
        return;
    }

    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void Image::DumpImage(std::string filename) {
    ImageLoader& loader = ImageLoader::GetInstance();
    if (pixels == nullptr) {
        return;
    }

    loader.DumpImage(width, height, pixels, filename);
}

void Image::Display_X_Server() {
    ImageLoader& loader = ImageLoader::GetInstance();
    if (pixels == nullptr) {
        return;
    }
    loader.Display_X_Server(width, height, pixels);
}

void Image::Display_ASCII() {
    ImageLoader& loader = ImageLoader::GetInstance();
    if (pixels == nullptr) {
        return;
    }
    loader.Display_ASCII(width, height, pixels);
}

void Image::Display_CMD() {
    ImageLoader& loader = ImageLoader::GetInstance();
    if (pixels == nullptr) {
        return;
    }
    loader.Display_CMD(width, height, pixels);
}
