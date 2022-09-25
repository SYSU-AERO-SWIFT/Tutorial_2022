#include "BG_H.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void Recovery::readVideo(string filePath)
{
	video.open(filePath);
	if (!video.isOpened())	//对video进行异常检测
	{
		cout << "video open error!" << endl;
		return;
	}
}

void Recovery::process()
{
	cout << "正在处理视频，请稍等" << endl;
	double time = static_cast<double>(getTickCount());
	int frame_num = video.get(CV_CAP_PROP_FRAME_COUNT);//获取总帧数
	Mat frame;//当前帧
	Mat before_frame;//前一帧
	Mat result_gray;//灰度图

	for (int i = 0; i < frame_num; i++)
	{
		if (frame_num > 300)//若帧数较多，可以抽帧加速
		{
			for (int j = 0; j < 2; j++) video >> frame;
		}
		video >> frame;
		if (frame.empty())//对帧进行检测
		{
			break;
		}

		int frame_position = video.get(CV_CAP_PROP_POS_FRAMES);//当前是第几帧
		//cout << "frame_position: " << frame_position << endl;

		if (frame_position == 1 || frame_position == 3) //如果为第一帧（before_frame还为空）
		{
			result_gray = track(frame, frame);//调用track()进行检测，返回值存入result_gray
			background = frame.clone();
			before_frame = frame.clone();
		}
		else if (frame_position <= 214)//用帧差法作为预处理
		{
			result_gray = track(before_frame, frame);//调用track()进行运动物体检测，返回值存入result_gray
			before_frame = frame.clone();
		}
		else
		{
			result_gray = track(background, frame);//调用track()进行运动物体检测，返回值存入result_gray
		}

		//更新 bg
		Mat tmp = frame.clone();
		background.copyTo(tmp, result_gray);
		addWeighted(background, 0.5, tmp, 0.5, 0, background);
	}
	time = ((double)getTickCount() - time) / getTickFrequency();
	cout << "背景提取成功" << endl;
	cout << "处理时间为：" << time << "秒" << endl;
	return;
}

void Recovery::showResult()
{
	namedWindow("background", 0);
	resizeWindow("background", 1024, 768);
	imshow("background", background);
	waitKey(0);
}

Mat Recovery::track(Mat background, Mat frame)
{
	//转为灰度图
	Mat gray1, gray2;
	cvtColor(background, gray1, CV_BGR2GRAY);
	cvtColor(frame, gray2, CV_BGR2GRAY);

	//做差,找到两帧之间不同点
	Mat diff;
	absdiff(gray1, gray2, diff);

	//阈值化处理
	Mat result;
	threshold(diff, result, 50, 255, CV_THRESH_BINARY);

	////腐蚀与膨胀（有了这个会使得轮廓的查找更加稳定，加强程序健壮性，但是对于修复本次任务三个视频没用，可以不用）
	//Mat result_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
	//Mat result_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));
	//erode(result, result, result_erode);
	//dilate(result, result, result_dilate);

	//查找轮廓
	vector<vector<Point>> contours;
	findContours(result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//画出图框
	vector<Rect> boundRect(contours.size());
	int x, y, w, h;
	// cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(contours[i]);
		x = boundRect[i].x;
		y = boundRect[i].y;
		w = boundRect[i].width;
		h = boundRect[i].height;
		//绘制
		rectangle(result, Point(x - 100, y - 100), Point(x + w + 100, y + h + 100), Scalar(255), CV_FILLED);//在x、y、w、h上加减是因为原来图框不够大，拖动时会有痕迹留下
	}
	return result;
}








