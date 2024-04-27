#include "photo_mosaic.h"

Data_Loader PhotoMosaic::data_loader;

PhotoMosaic::PhotoMosaic(){
    ;
}

PhotoMosaic::~PhotoMosaic(){
    ;
}

RGBImage* PhotoMosaic::run(string targetPath, string candidatePath){
    target_img.LoadImage(targetPath);
    target_img.Display_CMD();

    // return pointer
    RGBImage* result = new RGBImage(target_img.get_w(), target_img.get_h());

    data_loader.List_Directory(candidatePath, candidate_filenames);
    RGBImage candidates[10000];
    int imgNum = 0;
    for(const auto filename : candidate_filenames){
        if(candidates[imgNum].LoadImage(filename)){
            imgNum++;
        }
    }

    for(int row = 0; row < target_img.get_h() - SUB_PIC_SIZE; row += SUB_PIC_SIZE){
        for(int col = 0; col < target_img.get_w() - SUB_PIC_SIZE; col += SUB_PIC_SIZE){
            target_img.GridAverage(row, col, SUB_PIC_SIZE);

            // find the fittest candidate
            int candidate_idx = 0;
            double curMin = DBL_MAX;
            for(size_t i = 0; i < (size_t)imgNum; i++){
                double diff = candidates[i] - target_img;
                if(diff < curMin){
                    candidate_idx = i;
                    curMin = diff;
                }
            }

            // store candidate's pixel into result
            for(int i = row; i < row + SUB_PIC_SIZE; i++){
                for(int j = col; j < col + SUB_PIC_SIZE; j++){
                    result->pixels[i][j][0] = candidates[candidate_idx].pixels[i-row][j-col][0];
                    result->pixels[i][j][1] = candidates[candidate_idx].pixels[i-row][j-col][1];
                    result->pixels[i][j][2] = candidates[candidate_idx].pixels[i-row][j-col][2];
                }
            }
        }
    }
    return result;
}