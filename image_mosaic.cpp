#include<iostream>

#include "image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"

int main(int argc, char *argv[]){
    if (argc!=4) {
        std::cout << "Usage: " << argv[0] << " <target> <image dir> <output>\n";
        return 1;
    }

    Image *target = new RGBImage();
    if (!target->LoadImage(argv[1])) {
        std::cout << "Failed to load image\n";
        return 1;
    }

    Image *result = PhotoMosaic::Create(target, argv[2]);
    if (result == nullptr) {
        std::cout <<"Failed to create photo mosaic\n";
        return 1;
    }

    result->Display_X_Server();

    result->DumpImage(argv[3]);

    delete target;
    delete result;

    return 0;
}
