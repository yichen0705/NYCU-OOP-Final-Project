# OOP Final Project: Photo Mosaic

[![hackmd-github-sync-badge](https://hackmd.io/wL8VqoYNS_GaZTepscWhlA/badge)](https://hackmd.io/wL8VqoYNS_GaZTepscWhlA)


![image](https://hackmd.io/_uploads/By0sjAYbR.png)
如你所見，給定一張目標圖片，我們希望可以用很多張小圖拼湊出大圖的原貌。

[TOC]

## Preface
https://www.ptt.cc/bbs/Tech_Job/M.1711983745.A.0AB.html

## Step 1: Play around data loader class(12%)
因為圖片在存成jpg/png是有經過壓縮加密過的，因此若是學員要直接讀取圖片檔，會有不少問題。因此我撰寫了data_loader使學員可以直接得到圖片的像素矩陣及長寬，來進行後續的運算及操作。

此外，我也提供了三種介面來展示圖片: (1) X_Server (2)ASCII ART (3)catimg (直接在command line 秀出圖片)，來提供學員串接使用。

```c=
class Data_Loader{

public:
    Data_Loader();
    ~Data_Loader();
    int **Load_Gray(string filename, int *w, int *h);
    int ***Load_RGB(string filename, int *w, int *h);
    void Dump_Gray(int w, int h, int **pixels, string filename);
    void Dump_RGB(int w, int h, int ***pixels, string filename);
    void Display_Gray_X_Server(int w, int h, int **pixels);
    void Display_RGB_X_Server(int w, int h, int ***pixels);
    void Display_Gray_ASCII(int w, int h, int **pixels);
    void Display_RGB_ASCII(int w, int h, int ***pixels);
    void Display_Gray_CMD(string filename);
    void Display_RGB_CMD(string filename);
    bool List_Directory(string directoryPath, vector<string> &filenames);

private:
    bool File_Exists(const string &filename);
};
```

:::danger
Load回傳的dynamic allocate memory需要由學員自己負責刪除，我們會使用valgrind來檢查學員的程式，確保學員對每一個他們new出來的memory負責。
:::

## Step 2: Construct image inheritance and polymorphism(12%)

透過base class Image，來讓gray_image及rgb_image繼承，來讓同學練習繼承多型及virtual function。需要將第一步所提及的data_loader與這些class整合。來實現load image/dump image/display image，等基礎功能。

## Step 3: Bit-field with image filter design(12%)
參考大一計算機程式設計期末專題成果展: [連結](https://hackmd.io/@coherent17/ICP_Final_Image_Filter)

一般圖片在做影像處理演算法時，大多不會單一只透過一層filter的convolution，為求結果更好，可能會通過許多次的影像增強演算法。因此在這個部分，我們希望學員透過使用bit_field的方式，來指定要通過1~4種簡單影像處理的演算法。

ex:
```c=
#define BOX_FILTER          0b0001
#define SOBEL_GRADIENT      0b0010
#define NEGATIVE_FILTER     0b0100
#define CONTRAST_STRETCHING 0b1000

// bitwise or to load option:
int8_t option = BOX_FILTER | SOBEL_GRADIENT;
// option = 0b0011;

// bit wise and to determine
if(option & BOX_FILTER){
    // do box filter
}
if(option & SOBEL_GRADIENT){
    // do sobel gradient
}
```

## Step 4: Photo Mosaic(12%)

透過許多張小圖來當成大圖的像素。透過RGB channel的平均值來決定大圖中某個grid要由哪個小圖來代表。我們會提供常見的dataset: cifar10, mnist，來給學生當成小圖，大圖同學可以自行準備，抑或是使用我們提供的lena(最近被IEEE說不能再使用她的圖片當成benchmark了......)。

## Step 5: Documentation/QC/QA(12%)
在這個部分，同學不需要coding, 僅需要在報告中回答問題即可。
*    Q1:請大致解釋 `make install`做了甚麼事情。
*    Q2:makefile是如何協助編譯這份project的?(從inc/ src/回答)
*    Q3:在Step4中，你如何處理邊界問題?(若大圖的長寬不是小圖的倍數，你會怎麼處理?)
*    Q4:在Step4中，如果每張小圖的大小都不一樣，你會怎麼處理?
*    Q5:使用valgrind及cppcheck來對你的程式做動態分析與靜態分析，並秀出執行結果與報告。並解釋這兩種分析有何不同?(try to install cppcheck by your self...)

## Project Setup
```bash=
$ git clone https://github.com/coherent17/NYCU-OOP-Final-Project
$ cd NYCU-OOP-Final-Project/

# install the third party package
$ make install

# start programing your final project
# finish *.h in inc/ & *.cpp in src & main.cpp

# compile
$ make               # default
$ make VERBOSE=1     # check out what make actually do
$ make -j            # compile in parallel (save time, suggest)

# run your program
$ ./Image_Processing

# Dynamic memory check (Need to disable the Display_X_Server...)
$ make check
```
## Project Structure

```bash=
# show出project structure
$ tree -L 2
```

                    ├── Data-Loader(處理image I/O)
                    │   ├── data_loader.cpp
                    │   └── data_loader.h
                    ├── data_loader_demo.cpp(示範如何使用data_loader Step1)
                    ├── Image-Folder(放圖片的地方)
                    │   ├── 4k_owl.jpg
                    │   ├── cifar10
                    │   ├── girl_2x.png
                    │   ├── lena.jpg
                    │   └── mnist
                    ├── inc
                    │   ├── bit_field_filter.h(Step3)
                    │   ├── gray_image.h(Step2)
                    │   ├── image.h(Step2)
                    │   ├── photo_mosaic.h(Step4)
                    │   └── rgb_image.h(Step2)
                    ├── LICENSE
                    ├── main.cpp(Driven code)
                    ├── Makefile
                    ├── README.md
                    ├── scripts
                    │   └── clone_env.sh
                    ├── src
                    │   ├── bit_field_filter.cpp(Step3)
                    │   ├── gray_image.cpp(Step2)
                    │   ├── image.cpp(Step2)
                    │   ├── photo_mosaic.cpp(Step4)
                    │   └── rgb_image.cpp(Step2)
                    └── third-party(第三方開源圖片套件)
                        ├── catimg
                        ├── CImg
                        └── libjpeg

## Grading Policy
*    Step1~Step5(12% * 5 = 60%) 需要將結果秀在書面報告中
*    書面報告(15%)
        *    Step1~Step5結果圖
        *    解釋整份project中哪邊使用了繼承與多型
        *    分享你在這份project中遇到了甚麼困難
        *    跟其他組別比起來，你覺得你這組有什麼優勢?
        *    心得與回饋
*    額外功能(25%) 根據自己的興趣，自由發揮創意延伸

## Submission
*    Time: 2024/6/11(二) 13:00
*    File to submit: NYCU-OOP-Final-Project.tar & final_report.pdf
        ```bash=
        # 產生壓縮檔
        $ ls # 確認已跳到NYCU-OOP-Final-Project外面
        $ tar cvf NYCU-OOP-Final-Project.tar NYCU-OOP-Final-Project/
        $ ls # 產生NYCU-OOP-Final-Project.tar -> submit to e3

        # 解壓縮
        $ tar xvf NYCU-OOP-Final-Project.tar
        ```
:::info
請確認解壓縮後，可以在linux server上成功編譯並且執行。
:::

## Demo
*    Time: 2024/6/11(二) 14:00 ~16:00
*    Place: Online

:::info
在Linux中運行程式，詳細的呈現每一項功能，沒有demo的組別期末專題0分
:::

## Thanks for the following open source projects
*   CImg (https://github.com/GreycLab/CImg)
*   libjpeg (https://github.com/kornelski/libjpeg)
*   catimg (https://github.com/posva/catimg)