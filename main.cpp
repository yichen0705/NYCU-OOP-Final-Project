#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"

using namespace std;

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("/home/course/2024OOP/2024OOPTA/NYCU-OOP-Final-Project/lena.jpg");

    return 0;
}