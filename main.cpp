#include "image.h"
#include "rgb_image.h"
#include "image_filter.h"
#include "photo_mosaic.h"

int main(int argc, char *argv[]){
    Image *img = new RGBImage();
    img->LoadImage("Image-Folder/girl_2x.png");

    Image* result = PhotoMosaic::Create(img, "Image-Folder/cifar10");

    ImageFilterManager& mgr = ImageFilterManager::GetInstance();
    mgr.ApplyFilters(result, FILTER_INVERT);

    result->Display_X_Server();
    result->DumpImage("out.png");

    delete img;
    delete result;

    return 0;
}
