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
    * ����չʾ������ԭ��Ľ��
    */
    void showResult();

private:
    VideoCapture capture;
    Mat image;
};
#endif
