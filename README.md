# OOP Final Project: Photo Mosaic
Last Updated: 5/26
:::warning
Update Q&A section(新增QA部分在最後面!)  
寄信詢問前可以先看一下問題有沒有被問過!
:::

[![hackmd-github-sync-badge](https://hackmd.io/wL8VqoYNS_GaZTepscWhlA/badge)](https://hackmd.io/wL8VqoYNS_GaZTepscWhlA)


![image](https://hackmd.io/_uploads/By0sjAYbR.png)
如你所見，給定一張目標圖片，我們希望可以用很多張小圖拼湊出大圖的原貌。

[TOC]

## 解說影片
<iframe width="560" height="315" src="https://www.youtube.com/embed/GPI-fnaDGTk?si=yuDb7vlTXbLNm7Ic" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

## 誰適合寫這份題目?
*    對學習和探索新知識充滿熱情的人
*    對數位影像處理充滿熱情的人
*    具有上網搜索及自學能力者
*    想要推甄/轉系有作品集的

## 需要具備的能力
*    OOP
*    Dynamic Array
*    Pointer
*    Know how to use google.

## Preface: What is Digital Image?
數位影像是電腦處理的視覺資訊表現形式，與傳統模擬影像不同，它由離散的像素構成，每個像素包含特定的顏色和亮度資訊，而這些像素的排列形成了影像的整體視覺內容。

ex：8 位元灰階影像
*    位元深度：
        "8 位元"指的是每個像素的位深度。在 8 位元的灰階影像中，每個像素有 2^8（256）種可能的值，範圍從 0 到 255。
        
*    灰階(有多黑/有多白)：
不同於彩色影像，灰階影像包含各種灰色調。在 8 位元灰階影像中，每個像素代表不同的強度水平，其中 0 為黑色，255 為白色，中間有各種灰色調。
![image](https://hackmd.io/_uploads/ry0phvoW0.png)
Ref: [https://processing.org/tutorials/color]
![image](https://hackmd.io/_uploads/SkegTwj-0.png)

:::    success
因此，在電腦圖形中表示灰階影像是非常簡單的:使用一個二維陣列，裡面每個數值皆落在 0 到 255 的範圍。若是彩色圖片，則將其二維陣列擴展為有RGB三個channel的三維陣列即可。
:::
![image](https://hackmd.io/_uploads/B1IwawiW0.png)

## Step 1: Play around data loader class(15%)
圖片在存成jpg/png是有經過壓縮加密過的，若是學員要直接讀取圖片檔，會有不少問題。因此提供data_loader使學員可以直接得到圖片的像素矩陣及長寬，來進行後續的運算及操作。

以下是data_loader的interface:
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

這些interface的usage:
*    Load:
        ```c=
        int **Load_Gray(string filename, int *w, int *h);
        int ***Load_RGB(string filename, int *w, int *h);
        ```
        給定圖片的路徑，並且設定w與h，最後回傳一個二維(三維)陣列

        :::danger
        Load回傳的dynamic allocate memory需要由學員自己負責刪除，我們會使用valgrind來檢查學員的程式，確保學員對每一個他們new出來的memory負責。
        :::

*    Dump:
        ```c=
        void Dump_Gray(int w, int h, int **pixels, string filename);
        void Dump_RGB(int w, int h, int ***pixels, string filename);
        ```
        給定輸出的w,h,要輸出的二維(三維)陣列與要輸出的圖片檔名，會將圖片輸出成*jpg/*png。

data_loader提供了三種介面來展示圖片: 
*    1. X_Server
        使用moba_xterm中的Xserver來跳出視窗來顯示圖片。
        ```c=
        void Display_Gray_X_Server(int w, int h, int **pixels);
        void Display_RGB_X_Server(int w, int h, int ***pixels);
        ```
        
        ![image](https://hackmd.io/_uploads/BJZsWdjZC.png)
 
        :::danger
        因為valgrind在mem check時，無法辨認此function的部分macro expansion，因此在做memory leak check時，請不要使用此function。
        :::
 
*    2. ASCII ART
        使用" .-+#@"來表示圖片中的明暗程度，將圖片以符號的形式印在terminal。
        
        ```c=
        void Display_Gray_ASCII(int w, int h, int **pixels);
        void Display_RGB_ASCII(int w, int h, int ***pixels);
        ```
        ![image](https://hackmd.io/_uploads/HJvPGdiWC.png)

*    3. catimg 
        將圖片本身直接印在terminal，支援灰階及彩色圖片。

        ```c=
        void Display_Gray_CMD(string filename);
        void Display_RGB_CMD(string filename);
        ```

        ![image](https://hackmd.io/_uploads/r1FFM_s-R.png)

        :::info
        該function僅吃已存在的圖片檔的檔名，並把圖片印在terminal，請搭配前面所提到的dump使用。
        :::

*    filename iterator

        因為後面會需要學員處理多張照片，這邊提供一個method，來將某資料夾下的所有檔案名稱存進filenames的vector中。

        ```c=
        bool List_Directory(string directoryPath, vector<string> &filenames);
        ```

## Step 2: Construct image inheritance and polymorphism(15%)

透過base class Image，來讓gray_image及rgb_image繼承，來讓同學練習繼承多型及virtual function。需要將第一步所提及的data_loader與這些class整合。來實現load image/dump image/display image，等基礎功能。

繼承關係如下圖:
![image](https://hackmd.io/_uploads/HJGOMFs-R.png)


:::spoiler 點選展開繼承詳細指示
*    Base class: Image

        Data member:  
        *    int w(protected)
        *    int h(protected)
        *    Data_Loader data_loader(protected)
                :::info
                data_loader要讓所有image class來共用同一個data_loader，請查詢c++ keyword: static variable
                :::
        
        Member function(all public):
        *    Constructor/Destructor
        *    int get_w()
        *    int get_h()
        
        Pure virtual function(let derived class override, all public):
        *    bool LoadImage(string filename)
        *    void DumpImage(string filename)
        *    void Display_X_Server()
        *    void Display_ASCII()
        *    void Display_CMD()

*    Derived class: GrayImage (public inheritance Image)

        Data member:  
        *    int **pixels(private)

        Member function(all public):
        *    Constructor/Destructor

        Override Base class vitual function(all public):
        *    bool LoadImage(string filename)
        *    void DumpImage(string filename)
        *    void Display_X_Server()
        *    void Display_ASCII()
        *    void Display_CMD()
        
*    Derived class: RGBImage (public inheritance Image)

        Data member:  
        *    int ***pixels(private)

        Member function(all public):
        *    Constructor/Destructor

        Override Base class vitual function(all public):
        *    bool LoadImage(string filename)
        *    void DumpImage(string filename)
        *    void Display_X_Server()
        *    void Display_ASCII()
        *    void Display_CMD()
:::



:::info
學員需要將Step1所提到的data_loader所提供的method整合進這些class中，並且支援polymorphism中的dynamic binding(late binding/run time polymorphism)。
:::

ex:
```c=
Image *img1 = new GrayImage();
img1->LoadImage("Image-Folder/mnist/img_100.jpg");
img1->DumpImage("img1.jpg");
img1->Display_X_Server();
img1->Display_CMD();


Image *img2 = new RGBImage();
img2->LoadImage("Image-Folder/lena.jpg");
img2->DumpImage("img2.jpg");
img2->Display_X_Server();
img2->Display_CMD();
```
:::info
1. img1 and img2 are pointers to base class Image.  
2. GrayImage and RGBImage are derived classes of Image.  
3. The functions LoadImage, DumpImage, Display_X_Server, and Display_CMD are all virtual functions declared in the Image base class and overridden in the derived classes.
:::


## Step 3: Bit-field with image filter design(15%)
一般圖片在做影像處理演算法時，大多會通過許多次的影像增強演算法或是降躁銳化。因此在這個部分，我們希望學員透過使用bit_field的方式，來指定要通過1~4種簡單影像處理的演算法。

*    Bit field介紹:
```c=
//using bitfield to not to force user to passing all of the arguments
//using bitwise or to passing the options
//using bitwise and to get the info of the bitfield

#include <stdio.h>
#include <stdint.h>

#define CASE_ONE    0b00000001
#define CASE_TWO    0b00000010
#define CASE_THREE  0b00000100
#define CASE_FOUR   0b00001000


//using bitwise and to track whtat is the user's option
void loadCase(int8_t option){
    if(option & CASE_ONE)
        printf("Case 1 detected\n");
    if(option & CASE_TWO)
        printf("Case 2 detected\n");
    if(option & CASE_THREE)
        printf("Case 3 detected\n");
    if(option & CASE_FOUR)
        printf("Case 4 detected\n");
    printf("\n");
    printAndResult(option);
}

int main(){
    //test1:
    uint8_t option = 0b00001001;
    printf("test1:\n");
    loadCase(option);

    //test2:
    printf("test2:\n");
    loadCase(CASE_ONE | CASE_TWO);

    //test3:
    printf("test3:\n");
    loadCase(CASE_ONE | CASE_TWO | CASE_THREE | CASE_FOUR);
    return 0;
}
```
:::info
1. 透過`bitwise or` 來load不同的option
2. 透過`bitwise and` 來確認某個option是否有被enable
:::


以下列出幾個常見的影像處理演算法或是簡易的算式:

*    Box filter(用於模糊)
![image](https://hackmd.io/_uploads/SkslPYj-R.png)

*    Sobel Gradient(萃取出垂直與水平的線條)
![image](https://hackmd.io/_uploads/SyUfwFs-0.png)

*    Contrast Stretching(影像銳化)
![image](https://hackmd.io/_uploads/B14EwFj-R.png)

*    Mosaic filter(對照片打碼)
![image](https://hackmd.io/_uploads/BkvBvFibC.png)


學員可以參考大一上計算機程式設計期末專題成果展: [連結](https://hackmd.io/@coherent17/ICP_Final_Image_Filter)


:::info
預期同學實作任意四種以上的圖片影像處理的演算法，並透過bit field的概念來決定要enable哪幾個演算法。
:::

## Step 4: Photo Mosaic(15%)

透過許多張小圖來當成大圖的像素。透過RGB channel的平均值來決定大圖中某個grid要由哪個小圖來代表。我們會提供常見的dataset: cifar10, mnist，來給學生當成小圖，大圖同學可以自行準備，抑或是使用我們提供的放在Image-Folder內部的圖片。

預期學員撰寫一個class PhotoMosaic，並且與前面所建立好關係的Image繼承鍊及data loader整合，撰寫photo mosaic的演算法，希望提供一個函式介面，使使用者可以將放很多小圖的資料夾路徑傳入，及大圖的路徑傳入，而後回傳一個指標指向彩圖這個物件，使得使用者可以再使用這個物件來dump/display等等。
    
*    Algorithm (3 steps)  
        *    使用data_loader讀取target image  
        *    使用data_loader讀取所有的小圖  
        *    將target image進行分割並與所有小圖進行比較，挑選出rgb channel相差最少的小圖，而後將其填入回傳陣列中
:::info
何謂相差最小?  
1. 對所有的小圖算出紅色/綠色/藍色channel的所有像素的平均
2. 與大圖中partition出來的某個grid的紅色/綠色/藍色算差異平均的差異
$$
diff=\sqrt{r_{diff}^2+g_{diff}^2+b_{diff}^2}
$$
3. 選擇diff最小的小圖代表該大圖的grid
:::

[more algorithm reference & detail](https://www.geeksforgeeks.org/implementing-photomosaics/)

:::warning
學員可以在必要的情況下，針對class image gray_image rgb_image增加operator overloading/resize/crop等method，來協助實作photo mosaic的部分。
:::


感謝作者TA林煜睿提供照片測試:
![image](https://hackmd.io/_uploads/r13qhFi-R.png)

Zoom in:
![Zoom in girl](https://hackmd.io/_uploads/B1PvTKoWC.jpg)

## Driven Code for Step1~4
希望學員能夠設計一個清晰且優雅的使用者流程讓上面Step1~4與您所設計的加分項目都可以被demo到。若是單一一個main.cpp不夠您demo所有的功能，您可以自行設計其他driven code的檔案，並且更改`Makefile`中相關編譯的dependency與方法。

    
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
                    ├── inc (put your header here)
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
                    ├── src (put your implementation here)
                    │   ├── bit_field_filter.cpp(Step3)
                    │   ├── gray_image.cpp(Step2)
                    │   ├── image.cpp(Step2)
                    │   ├── photo_mosaic.cpp(Step4)
                    │   └── rgb_image.cpp(Step2)
                    └── third-party(第三方開源圖片套件)
                        ├── catimg
                        ├── CImg
                        └── libjpeg

將class header interface放在inc folder內部，並且將source code的實作放在src folder內部，makefile會自動去識別dependency，並且在您對某些檔案進行修改後，僅編譯需要重新編譯之檔案，不會整份project重新編譯一次，如此一來再搭配上parallel compile，讓您再開發上能夠節省不少時間。

## Grading Policy
*    Step1~Step4(15% * 4 = 60%) 需要將結果秀在書面報告中
:::info
請將QA及書面報告整理在一份pdf報告中!
:::
*    QA(6%)
        *    Q1:請大致解釋 `make install`做了甚麼事情。
        *    Q2:makefile是如何協助編譯這份project的?(從inc/ src/回答)
        *    Q3:請解釋在Step3中如何設計bit field演算法，如何決定要使用多少bit，這樣做有甚麼優點?
        *    Q4:在Step4中，你如何處理邊界問題?(若大圖的長寬不是小圖的倍數，你會怎麼處理?)
        *    Q5:在Step4中，如果每張小圖的大小都不一樣，你會怎麼處理?
        *    Q6:使用valgrind及cppcheck來對你的程式做動態分析與靜態分析，並秀出執行結果與報告。並解釋這兩種分析有何不同?(try to install cppcheck by your self...)

*    書面報告(9%)
        *    Step1~Step5結果圖
        *    解釋整份project中哪邊使用了繼承與多型，對於Step3&4及你的加分題是如何與其他的class互動的?eg: friend class, another inheritance?請使用類似Step2那張class之間的關係圖清楚的表示。
        *    分享你在這份project中遇到了甚麼困難，又是如何解決的?
        *    跟其他組別比起來，你覺得你這組有什麼優勢?
        *    心得與回饋

*    額外功能(25%) 根據自己的興趣，自由發揮創意延伸
        *    鼓勵大家貢獻自己的程式到開源社群，上傳project到github得到2分。(需附上project repo)並且盡早建立如何做好程式專案版本控制(version control)及如何與團隊協作專案的能力。 [ref link](https://github.com/twtrubiks/Git-Tutorials)  
        (先fork repo，再git clone -> commit -> push to your own repo)  
        
        或是你直接開一個新的repo，直接整包上傳上去，不會的話再來信詢問!
        *    Image Segamentation(影像分割)
        *    Photo Mosaic with only 1 picture [IEEE paper](https://ieeexplore.ieee.org/document/7965140)
        ![image](https://hackmd.io/_uploads/r171Wpq-C.png)
        *    Parallel Algorithm Implementation(MPI/pthread/cuda): NTHU PP周志遠教授

                <iframe width="560" height="315" src="https://www.youtube.com/embed/t_q0Tajpyso?si=zQekxMCXDOAkGfTa" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

        *    Design Pattern: [ref link](https://refactoring.guru/design-patterns/cpp)  
                C++中的設計模式很重要，因為它們提供了解決常見問題的有效方法。在這門課中，僅有教學員簡單的OOP語法，並沒有教導學員如何撰寫出有品味，可重複使用，可維護性及可擴展性的程式碼。Design Pattern，是一種OOP程式的模板，遇到某種問題，便可以套用這些模板來使用，來減少錯誤的發生並且提高程式的重用性、可擴展性和可維護性，並且有助於團隊間的溝通和遵循最佳實踐。
        
:::info
以上為我所推薦的幾個加分題的方向，學員不需要侷限在這些題目中，可以自行發想有趣的題目。
:::

## Submission
*    Time: 2024/6/17(二) 12:00
*    File to submit: `NYCU-OOP-Final-Project.tar` & `final_report.pdf`
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
*    Time: 2024/6/17(一) 14:00 ~16:00
*    Place: Online

:::info
在Linux中運行程式，詳細的呈現每一項功能，沒有demo的組別期末專題0分
:::

## TA groups
*    何祁恩: mnb51817@gmail.com
*    林煜睿: yrlin719.ee12@nycu.edu.tw
*    張理為: reeveschang.ee12@nycu.edu.tw
*    李品賢: bb1456983.ee12@nycu.edu.tw
*    劉映廷: dacy8864@gmail.com
*    欉家新: tsungnewly@gmail.com

:::warning
寄信問助教問題請一律寄給所有助教，包括過程中所有的回覆應答，請使用"回覆所有人"。
:::

## Thanks for the following open source projects
*   CImg (https://github.com/GreycLab/CImg)
*   libjpeg (https://github.com/kornelski/libjpeg)
*   catimg (https://github.com/posva/catimg)

## Q&A

*    Q1:
關於期末專題的memory leak check，有提到跟X_Server有關的function會影響檢查的結果，檢查時不要用這個function，想請問具體是要在哪些地方disable掉這個function呢?

        :::spoiler
        與X_server相關的function因為valgrind尚未將這個display的function列入考慮，因此會有false alarm的問題在，在錯誤訊息中也可以看到valgrind有自己承認他不能識別該function。至於要如何disable，你可以就單純把需要使用到X_server的時候註解掉即可。此時valgrind便不會執行到該function，便不會有相關問題。
        
        好一點的註解方法: (善用flag)
        ```bash=
        #define ENABLE_X_SERVER false

        if(ENABLE_X_SERVER){
            //X_Server command here
        }
        ```
        
        ![image](https://hackmd.io/_uploads/BJcaPN3mR.png)
        上圖為valgrind沒有disable X_server相關command的警示訊息，給同學參考。
        :::

*    Q2:
有些圖片為何經過data_loader讀取後會發生錯誤?

        :::spoiler
        有些圖片除了R、G、B三個通道外，還會帶有第四個代表透明度的alpha通道，由於先前Data_Loader中Load_RGB所定義的pixels為三通道，因此讀取後會產生錯誤。這種問題會出現在某些png圖片中而不可能發生於jpg圖片，因為png才會有透明屬性，jpg則無。
        
        因此我們修改Data_Loader中Load_RGB，首先創建Dynamic Array時直接限制為三通道(不再根據_c創建對應大小的陣列，因為_c有可能為4)，並限制其只填寫前三個通道的數值至pixels中(即不填寫alpha通道的數值)。同理，Load_Gray我們也做了相應的處理。
        
        因此最後同學透過Data_Loader Load_RGB與Load_Gray所讀取的結果將不再帶有alpha屬性，只要當作正常三通道(RGB)或是單通道(灰階)的圖片進行操作即可。
        
        如果同學已經開始實作的話，請依照下列步驟將Data_Loader.cpp更新至最新的版本:
        ```bash=
        $ cd NYCU-OOP-Final-Project
        $ git pull
        ```
        如此便可單純更新data_loader.cpp中的內容，而不會更改同學已經實作的部分。
        
        相關資料同學可以參閱此網站: https://reurl.cc/OMmpRD
        :::
    

*    Q3:
GrayImage 和 RGBImage class 中的CMD要呼叫datal_oader裡的Diaplay_Gray_CMD、Display_RGB_CMD function，但我們不知道filename要去哪裡抓，請助教們解惑。

        :::spoiler
        這邊其實有點tricky,算是我想要考你們的其中一個點：中間檔案的產出。

        有時候在程式執行中，不免會產生一些中間的檔案，可能是log(程式執行上的一些紀錄），抑或是其他程式或是function會需要吃的特定format 的output file 。

        這邊我有提示需要搭配dump 來使用，可以先產生一個暫時的輸出圖片，使用CMD相關function之後（內部實作其實是去call catimg 的binary 執行檔），再使用system call的方法將該暫時出現的圖片刪除。查詢C/C++ system()的使用方式，配搭之前之前上機課教過的linux command 即可在c++中刪除該中間產生的圖片檔！
        :::