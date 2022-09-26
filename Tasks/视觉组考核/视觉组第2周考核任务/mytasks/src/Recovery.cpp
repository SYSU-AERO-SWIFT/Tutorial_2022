#include "/home/steve/opencv/include/opencv2/opencv.hpp"
#include<string>
#include <chrono>
#include <map>
#include <vector>
#include"Recovery.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

void Recovery::readVideo(String filePath) {
	capture.open(filePath);
}

void Recovery::process() {
	auto start = system_clock::now();
	Mat frame;
	int n = 0;
	int w, d, dim;
	image = Mat::zeros(frame.size(), frame.type());
	capture >> frame;
	w = frame.cols;
	d = frame.rows;
	dim = frame.channels();
	vector<vector<map<int, int>>> count[3];
	for (int k = 0; k < 3; ++k) {
		count[k] = {};
		for (int i = 0; i < d; ++i) {
			count[k].push_back({});
			for (int j = 0; j < w; ++j) {
				map<int, int> mymap;
				count[k][i].push_back(mymap);
			}
		}
	}
	while (true) {
		capture >> frame;
		if (n == 0) {
			image = frame.clone();
		}
		if (frame.empty()) {
			break;
		}
		///*video2中帧数较高，舍去部分帧数让障碍物不会出现拖动的情况，降低噪点影响同时加速
		//  video0 video1帧数较低可以不用舍去*/
		//if (n % 15) {
		//	++n;
		//	continue;
		//}
		for (int i = 0; i < d; ++i) {
			uchar* current_row1 = frame.ptr<uchar>(i);
			uchar* current_row2 = image.ptr<uchar>(i);
			for (int j = 0; j < w; ++j) {
				for (int k = 0; k < 3; ++k) {
					++count[k][i][j][*current_row1];
					if (count[k][i][j][*current_row2] < count[k][i][j][*current_row1]) {
						*current_row2 = *current_row1;
					}
					++current_row1;
					++current_row2;
				}
			}
		}
		++n;
		//video1 video2中末尾部分障碍物停留时间较长，舍去后半部分降低噪点影响
		if (n == 200) {
			break;
		}
	}
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "Process time:"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den
		<< "s" << endl;
}

void Recovery::showResult() {
	namedWindow("Result:", WINDOW_FREERATIO);
	imshow("Result:", image);
	waitKey(0);
	destroyAllWindows();
}
