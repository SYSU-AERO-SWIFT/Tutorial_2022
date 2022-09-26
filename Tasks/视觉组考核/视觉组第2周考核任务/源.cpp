#include<opencv2\opencv.hpp>
#include <quickopencv.h>
#include<iostream>
#include<math.h>
#include<unordered_map>
using namespace std;
using namespace cv;
int main() {
	VideoCapture capture("D:/xuniji/video2.mp4");
	Mat frame;
	namedWindow("frame", WINDOW_FREERATIO);
	namedWindow("ans2", WINDOW_FREERATIO);
	Mat m3;
	VideoCapture capture1("D:/xuniji/video2.mp4");
	capture1.read(m3);
	Mat ans2 = Mat::zeros(m3.size(), m3.type());
	Mat m1 = Mat::zeros(m3.size(), m3.type());
	Mat m2;
	int h = m3.rows;
	int w = m3.cols;
	int frame_count = capture.get(CAP_PROP_FRAME_COUNT);
	vector<Mat> des;
	int count = 0;
	while (true) {
		capture.read(frame);
		if (frame_count < 50) {
			if (frame.empty())break;
		}
		else {
			if (frame.empty()) {
				capture.set(cv::CAP_PROP_POS_FRAMES, 0);
				continue;
			}
			count++;
			if (count == 2000)break;
			if (count % 9 != 0)continue;
		}
		imshow("frame", frame);
		waitKey(1);
		Mat m1 = frame.clone();
		des.push_back(m1);
	}
	vector<Mat> ans;
			for (int i = 0; i < des.size(); i+=2) {
				for (int j = 0; j < h; j++) {
					for (int k = 0; k < w; k++) {
						if (i != des.size() - 1) {
							if ((des[i].at<Vec3b>(j, k) == des[i + 1].at<Vec3b>(j, k))) {
								ans2.at<Vec3b>(j, k) = des[i].at<Vec3b>(j, k);
							}
							/*if (des[i].at<Vec3b>(j, k)[1] == des[i + 1].at<Vec3b>(j, k)[1]) {
								ans2.at<Vec3b>(j, k)[1] = des[i].at<Vec3b>(j, k)[1];
							}
							if (des[i].at<Vec3b>(j, k)[2] == des[i + 1].at<Vec3b>(j, k)[2]) {
								ans2.at<Vec3b>(j, k)[2] = des[i].at<Vec3b>(j, k)[2];
							}*/
						}
					}
				}ans.push_back(ans2);
			}
			for (int i = 0; i < ans.size(); i+=2) {
				for (int j = 0; j < h; j++) {
					for (int k = 0; k < w; k++) {
						if (i != ans.size() - 1) {
							if ((ans[i].at<Vec3b>(j, k) == ans[i + 1].at<Vec3b>(j, k))) {
								ans2.at<Vec3b>(j, k) = ans[i].at<Vec3b>(j, k);
	
							}
						}
					}
				}
			}

	imshow("ans2", ans2);
	imwrite("D:/xuniji/video2.jpg", ans2);
	waitKey(0);
	destroyAllWindows();
	return 0;
}