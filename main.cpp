#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include <vector>

using namespace std;
using namespace cimg_library;

int main(int argc, char *argv[]){
    
    
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    img1->Display_X_Server();
    img1->Display_ASCII();
    img1->Display_CMD();
    

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    img2->Display_X_Server();
    img2->Display_ASCII();
    img2->Display_CMD();

    PhotoMosaic photomosaic;
    RGBImage* result = photomosaic.run("Image-Folder/girl_2x.png","Image-Folder/cifar10");
    result->DumpImage("img3.jpg");

    return 0;
}
