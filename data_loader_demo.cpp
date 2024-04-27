#include "data_loader.h"
#include <vector>

int main(){
    Data_Loader data_loader;
    
    // 1. Load gray image
    int w1;
    int h1;
    int **pixels1 = data_loader.Load_Gray("Image-Folder/mnist/img_0.jpg", &w1, &h1);
    data_loader.Dump_Gray(w1, h1, pixels1, string("pixels1.jpg"));
    data_loader.Display_Gray_X_Server(w1, h1, pixels1);
    data_loader.Display_Gray_ASCII(w1, h1, pixels1);
    data_loader.Display_Gray_CMD("pixels1.jpg");

    // 2. Load rgb image into gray scale image
    int w2;
    int h2;
    int **pixels2 = data_loader.Load_Gray("Image-Folder/lena.jpg", &w2, &h2);
    data_loader.Dump_Gray(w2, h2, pixels2, string("pixels2.jpg"));
    data_loader.Display_Gray_X_Server(w2, h2, pixels2);
    data_loader.Display_Gray_CMD("pixels2.jpg");

    // 3. Load rgb image
    int w3;
    int h3;
    int ***pixels3 = data_loader.Load_RGB("Image-Folder/cifar10/airplane_0010.png", &w3, &h3);
    data_loader.Dump_RGB(w3, h3, pixels3, string("pixels3.jpg"));
    data_loader.Display_RGB_X_Server(w3, h3, pixels3);
    data_loader.Display_RGB_ASCII(w3, h3, pixels3);
    data_loader.Display_RGB_CMD("pixels3.jpg");

    // 4. List Directory
    vector<string> filenames;
    data_loader.List_Directory("Image-Folder/mnist", filenames);
    for(const auto &filename : filenames){
        cout << filename << endl;
    }
}