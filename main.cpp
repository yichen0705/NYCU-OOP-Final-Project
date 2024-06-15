#include "image.h"
#include "rgb_image.h"
#include "image_filter.h"

int main(int argc, char *argv[]){
    Image *img = new RGBImage();
    img->LoadImage("Image-Folder/lena.jpg");

    ImageFilterManager& mgr = ImageFilterManager::GetInstance();
    mgr.ApplyFilters(img, FILTER_SWIRL);

    img->Display_X_Server();
    return 0;
}
