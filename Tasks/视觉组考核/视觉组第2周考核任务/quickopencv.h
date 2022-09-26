#pragma once
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
class Recovery {

public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
    void readVideo(String filePath);

    /* process
    * 进行还原过程
    */
    void process();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();
private:
    Mat frame;//每一帧
    Mat ans;//答案
    vector<vector<unordered_map<uchar, int>>> picture[3];//用来保存三通道的每一帧每一个像素点的颜色出现次数
    vector<vector<pair<uchar, int>>> res[3];//存放三通道的每一帧每一个像素点的颜色出现次数最多的结果
    int height = 0;//每一帧的高
    int width = 0;//每一帧的宽
    int frame_count = 0;//视频总帧数
};
