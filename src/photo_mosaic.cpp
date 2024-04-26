#include "photo_mosaic.h"

Data_Loader PhotoMosaic::data_loader(0);

PhotoMosaic::PhotoMosaic(){
    result = nullptr;
}

PhotoMosaic::~PhotoMosaic(){
    for(const auto &candidate : candidates){
        delete candidate;
    }
}

int ***PhotoMosaic::run(string targetPath, string candidatePath){
    target_img.LoadImage(targetPath);
    target_img.Display_CMD();

    // allocate for the return matrix
    result = new int**[target_img.get_h()];
    for(int i = 0; i < target_img.get_h(); i++){
        result[i] = new int*[target_img.get_w()];
        for(int j = 0; j < target_img.get_w(); j++){
            result[i][j] = new int[3];
        }
    }

    for(int i = 0; i < target_img.get_h(); i++){
        for(int j = 0; j < target_img.get_w(); j++){
            for(int k = 0; k < 3; k++){
                result[i][j][k] = 0;
            }
        }
    }

    data_loader.List_Directory(candidatePath, candidate_filenames);
    for(const auto filename : candidate_filenames){
        RGBImage *img = new RGBImage;
        cout << filename << endl;
        if(img->LoadImage(filename)) candidates.emplace_back(img);
    }

    for(int row = 0; row < target_img.get_h() - SUB_PIC_SIZE; row += SUB_PIC_SIZE){
        for(int col = 0; col < target_img.get_w() - SUB_PIC_SIZE; col += SUB_PIC_SIZE){
            target_img.GridAverage(row, col, SUB_PIC_SIZE);

            // find the fittest candidate
            int candidate_idx = 0;
            double curMin = DBL_MAX;
            for(size_t i = 0; i < candidates.size(); i++){
                double diff = *(candidates[i]) - target_img;
                if(diff < curMin){
                    candidate_idx = i;
                    curMin = diff;
                }
            }

            // store candidate's pixel into result
            for(int i = row; i < row + SUB_PIC_SIZE; i++){
                for(int j = col; j < col + SUB_PIC_SIZE; j++){
                    result[i][j][0] = candidates[candidate_idx]->pixels[i-row][j-col][0];
                    result[i][j][1] = candidates[candidate_idx]->pixels[i-row][j-col][1];
                    result[i][j][2] = candidates[candidate_idx]->pixels[i-row][j-col][2];
                }
            }
        }
    }
    data_loader.Display_RGB_X_Server(target_img.get_w(), target_img.get_h(), result);
    return result;
}