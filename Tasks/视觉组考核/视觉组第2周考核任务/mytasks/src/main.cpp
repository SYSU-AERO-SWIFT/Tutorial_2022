#include<opencv.hpp>
#include<string>
#include"Recovery.hpp"

using namespace std;
using namespace cv;

int main() {
	Recovery r;
	r.readVideo("D:/GitHub/Tutorial_2022/resource/video0.mp4");
	r.process();
	r.showResult();

	return 0;
}