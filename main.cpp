#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"

using namespace std;

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/lena.jpg");

    return 0;
}