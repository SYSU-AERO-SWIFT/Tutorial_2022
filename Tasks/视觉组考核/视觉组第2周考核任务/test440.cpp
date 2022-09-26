#include<opencv2\opencv.hpp>
#include <quickopencv.h>
#include<iostream>
#include<math.h>
#include<unordered_map>
using namespace std;
using namespace cv;
int main() {
	Recovery test;
	test.readVideo("D:/xuniji/video0.mp4");
	test.process();
	test.showResult();
	return 0;
}
