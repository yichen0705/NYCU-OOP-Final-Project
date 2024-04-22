#include "photo_mosaic.h"

#define SUB_PIC_SIZE 32

PhotoMosaic::PhotoMosaic(){
    ;
}

PhotoMosaic::~PhotoMosaic(){
    ;
}

int*** PhotoMosaic::run(string targetPath, string candidatePath){
    // Load target image
    RGBImage tarImg;
    tarImg.LoadImage(targetPath);
    
    // initialize result array
    int*** result = new int**[tarImg.get_h()];
    for(int i = 0; i < tarImg.get_h(); i++){
        result[i] = new int*[tarImg.get_w()];
        for(int j = 0; j < tarImg.get_w(); j++){
            result[i][j] = new int[3];
        }
    }
    for(int i = 0; i < tarImg.get_h(); i++){
        for(int j = 0; j < tarImg.get_w(); j++){
            for(int k = 0; k < 3; k++){
                result[i][j][k] = 0;
            }
        }
    }

    // Check each small image inside cifar100,
    // then find the most fittest image and store it into img.pixels
    vector<string> fileNames;

    data_loader.List_Directory(string(candidatePath),fileNames);
    // for(string fileName:fileNames){
    //     cout << fileName << '\n';
    // }

    for(string fileName:fileNames){
        if(fileName == candidatePath + "/." || fileName == candidatePath + "/..") continue;
        cout << fileName << '\n';
        RGBImage candidate;
        candidate.LoadImage(fileName);
        candidates.push_back(candidate);
    }


    // for(int row = 0; row < tarImg.get_h()-SUB_PIC_SIZE; row += SUB_PIC_SIZE){
    //     for(int col = 0; col < tarImg.get_w()-SUB_PIC_SIZE; col += SUB_PIC_SIZE){
    //         RGBImage subImg;
    //         subImg.calAverage(row,col);

    //         // find the fittest candidate
    //         int candidate_idx = 0;
    //         double curMin = INT_MAX;
    //         for(int i = 0; i < candidates.size(); i++){
    //             RGBImage candidate = candidates[i];
    //             double diff = candidate - subImg;
    //             if(diff < curMin){
    //                 candidate_idx = i;
    //                 curMin = diff;
    //             }
    //         }

    //         // store candidate's pixel into result
    //         for(int i = row; i < row+32; i++){
    //             for(int j = col; j < col+32; j++){
    //                 result[i][j][0] = candidates[candidate_idx].pixels[i-row][j-col][0];
    //                 result[i][j][1] = candidates[candidate_idx].pixels[i-row][j-col][1];
    //                 result[i][j][2] = candidates[candidate_idx].pixels[i-row][j-col][2];
    //             }
    //         }


    //     }
    // }

    // data_loader.Display_RGB(tarImg.get_w(), tarImg.get_h(), result);

    return result;
}