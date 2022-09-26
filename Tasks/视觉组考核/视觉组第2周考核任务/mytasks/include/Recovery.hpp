#ifndef RECOVERY_HPP
#define RECOVERY_HPP
#include<opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

class Recovery {
    
public:
    void readVideo(String filePath);

    void process();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();

private:
    VideoCapture capture;
    Mat image;
};
#endif
