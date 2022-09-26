#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace cv;
using namespace std;
class Recovery {
private:

	//容器data用于存放每一帧图像的每一个像素点的像素值以及该值的出现次数
	vector<vector<unordered_map<uchar, int>>> data[3];

	//容器max用于记录每一帧图像的每一个像素点出现次数最多的像素值
	vector<vector<pair<uchar, int>>>  max[3];

	int frame_count=0;
	Mat src;
	Mat dst;
	VideoCapture cap;
public:

	void process(string readpath);

	void saveAndShowResult(string savepath);
};
