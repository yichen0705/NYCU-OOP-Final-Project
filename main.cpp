#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    vector<string> filenames;
    
    // Image *img1 = new GrayImage();
    // listdir("Image-Folder/mnist/", filenames);
    // for(const auto &img : filenames){
    //     if(img == "." || img == "..") continue;
    //     cout << img << endl;
    //     img1->LoadImage("Image-Folder/mnist/" + img);
    // }
    // img1->LoadImage("Image-Folder/mnist/trainingSample/9/img_100.jpg");
    
    // Image *img1 = new GrayImage();
    // img1->LoadImage("Image-Folder/lena.jpg");

    // Image *img2 = new RGBImage();
    // img2->LoadImage("Image-Folder/lena.jpg");

    // listdir_2("Image-Folder/cifar100_png/test", filenames);

    PhotoMosaic pm;
    int*** result = pm.run("Image-Folder/lena.jpg","Image-Folder/cifar100_png/train/apple");

    return 0;
}