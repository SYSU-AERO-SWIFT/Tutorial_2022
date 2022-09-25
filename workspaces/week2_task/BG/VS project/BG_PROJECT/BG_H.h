#ifndef _BG_H_
#define _BG_H_
#include<iostream>
#include<string>
#include <opencv2/opencv.hpp>
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