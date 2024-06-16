#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    // img1->DumpImage("img1.jpg");
    img1->Display_ASCII();
    

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/pikachu.jpg");
    // img2->DumpImage("img2.jpg");
    img2->Display_CMD();
    img2->Display_X_Server();

    return 0;
}