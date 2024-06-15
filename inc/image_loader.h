#ifndef IMAGE_LOADER
#define IMAGE_LOADER

#include <string>

#include "data_loader.h"
#include "color.h"

class ImageLoader {
public:
    static ImageLoader& GetInstance() {
        static ImageLoader instance;
        return instance;
    }

    Color** LoadImage(std::string filename, int& width, int& height, bool gray);
    void DumpImage(int width, int height, Color** pixels, std::string filename);
    void Display_X_Server(int width, int height, Color** pixels);
    void Display_ASCII(int width, int height, Color** pixels);
    void Display_CMD(int width, int height, Color** pixels);

    bool ListDirectory(std::string directory_path, std::vector<std::string> &filenames);
 
private:
    ImageLoader() = default;
    Data_Loader data_loader;

public:
    ImageLoader(ImageLoader const&) = delete;
    void operator=(ImageLoader const&) = delete;
};

#endif
