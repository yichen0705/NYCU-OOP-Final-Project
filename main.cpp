#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <dirent.h>
#include <vector>

using namespace std;

int listdir(const char *path, vector<string> &filenames) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return -1;
    }

    while ((entry = readdir(dp))){
        filenames.push_back(string(entry->d_name));
    }

    closedir(dp);
    return 0;
}

int main(int argc, char *argv[]){
    vector<string> filenames;
    Image *img1 = new GrayImage();
    // listdir("Image-Folder/mnist/", filenames);
    // for(const auto &img : filenames){
    //     if(img == "." || img == "..") continue;
    //     cout << img << endl;
    //     img1->LoadImage("Image-Folder/mnist/" + img);
    // }
    // img1->LoadImage("Image-Folder/mnist/trainingSample/9/img_100.jpg");
    img1->LoadImage("Image-Folder/lena.jpg");

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    return 0;
}