#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    vector<string> filenames;
    
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
    // Image *img1 = new GrayImage();
    // img1->LoadImage("Image-Folder/lena.jpg");

    // Image *img2 = new RGBImage();
    // img2->LoadImage("Image-Folder/lena.jpg");

    // listdir_2("Image-Folder/cifar100_png/test", filenames);

    // PhotoMosaic pm;
    // int*** result = pm.run("Image-Folder/lena.jpg","Image-Folder/mnist");

    return 0;
}