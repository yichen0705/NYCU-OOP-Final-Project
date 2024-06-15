#include "image_loader.h"

#include <cstdio>

static Color** allocatePixels(int width, int height) {
    Color** pixels = new Color*[height];
    if (pixels == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < height; i++) {
        pixels[i] = new Color[width];
        if (pixels[i] == nullptr) {
            return nullptr;
        }
    }

    return pixels;
}

static void freeDataRGB(int width, int height, int*** data) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete[] data[i][j];
        }
        delete[] data[i];
    }
    delete[] data;
}

Color** ImageLoader::LoadImage(std::string filename, int& width, int& height, bool gray) {
    Color** pixels = nullptr;
    
    if (gray) {
        int** data = data_loader.Load_Gray(filename, &width, &height);
        if (data == nullptr) {
            return nullptr;
        }

        pixels = allocatePixels(width, height);
        if (pixels == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pixels[i][j].r = data[i][j];
                pixels[i][j].g = data[i][j];
                pixels[i][j].b = data[i][j];
                pixels[i][j].a = 255;
            }
        }

        for (int i = 0; i < height; i++) {
            delete[] data[i];
        }
        delete[] data;
    } else {
        int*** data = data_loader.Load_RGB(filename, &width, &height);
        if (data == nullptr) {
            return nullptr;
        }

        pixels = allocatePixels(width, height);
        if (pixels == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pixels[i][j].r = data[i][j][0];
                pixels[i][j].g = data[i][j][1];
                pixels[i][j].b = data[i][j][2];
                pixels[i][j].a = 255;
            }
        }

        freeDataRGB(width, height, data);
    }

    return pixels;
}

static int*** colorToDataRGB(int width, int height, Color** pixels) {
    int*** data = new int**[height];
    if (data == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < height; i++) {
        data[i] = new int*[width];
        if (data[i] == nullptr) {
            return nullptr;
        }

        for (int j = 0; j < width; j++) {
            data[i][j] = new int[3];
            if (data[i][j] == nullptr) {
                return nullptr;
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            data[i][j][0] = pixels[i][j].r;
            data[i][j][1] = pixels[i][j].g;
            data[i][j][2] = pixels[i][j].b;
        }
    }

    return data;
}

void ImageLoader::DumpImage(int width, int height, Color** pixels, std::string filename) {
    int*** data = colorToDataRGB(width, height, pixels);
    if (data == nullptr) {
        std::cout << "failed to allocate memory" << std::endl;
    }

    data_loader.Dump_RGB(width, height, data, filename);

    freeDataRGB(width, height, data);
}

void ImageLoader::Display_X_Server(int width, int height, Color** pixels) {
    int*** data = colorToDataRGB(width, height, pixels);
    if (data == nullptr) {
        std::cout << "failed to allocate memory" << std::endl;
    }

    data_loader.Display_RGB_X_Server(width, height, data);

    freeDataRGB(width, height, data);
}

void ImageLoader::Display_ASCII(int width, int height, Color** pixels) {
    int*** data = colorToDataRGB(width, height, pixels);
    if (data == nullptr) {
        std::cout << "failed to allocate memory" << std::endl;
    }

    data_loader.Display_RGB_ASCII(width, height, data);

    freeDataRGB(width, height, data);
}

void ImageLoader::Display_CMD(int width, int height, Color** pixels) {
    int*** data = colorToDataRGB(width, height, pixels);
    if (data == nullptr) {
        std::cout << "failed to allocate memory" << std::endl;
    }

    const char* filename = "temp.jpg";
    data_loader.Dump_RGB(width, height, data, filename);
    data_loader.Display_RGB_CMD(filename);
    std::remove(filename);

    freeDataRGB(width, height, data);
}

bool ImageLoader::ListDirectory(std::string directory_path, std::vector<std::string> &filenames) {
    return data_loader.List_Directory(directory_path, filenames);
}
