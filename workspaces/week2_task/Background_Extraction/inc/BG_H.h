#ifndef _BG_H_
#define _BG_H_
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
class Recovery {
public:
    void readVideo(string filePath);
    void process();
    void showResult();
    Mat track(Mat background, Mat frame);
private:
    string filePath;
    VideoCapture video;
    Mat background;
};
#endif _BG_H_
