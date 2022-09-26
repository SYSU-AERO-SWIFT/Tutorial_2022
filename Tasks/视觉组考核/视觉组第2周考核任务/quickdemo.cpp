#include <quickopencv.h>
void Recovery::readVideo(String filePath) {
	VideoCapture capture(filePath);
	Mat temp;
	capture >> temp;
	ans = Mat(temp.size(), temp.type());
	height = temp.rows;
	width = temp.cols;
	frame_count = capture.get(CAP_PROP_FRAME_COUNT);
	//对两个存放像素点颜色的容器进行初始化，不然会报错
	for (int i = 0; i < 3; i++) {
		picture->push_back({});
		res->push_back({});
		for (int row = 0; row < height; row++) {
			picture[i].push_back({});
			res[i].push_back({});
			for (int col = 0; col < width; col++) {
				unordered_map<uchar, int> temp1;
				pair<uchar, int> temp2;
				picture[i][row].push_back(temp1);
				res[i][row].push_back(temp2);
			}
		}
	}
	//把视频的每一帧的每一个像素点的颜色出现次数都放进picture容器里面
	while (1) {
		capture.read(frame);
		namedWindow("frame", WINDOW_FREERATIO);
		if (frame.empty())break;
		imshow("frame", frame);
		waitKey(1);
		for (int row = 0; row < height; row++) {
			uchar* current = frame.ptr<uchar>(row);
			for (int col = 0; col < width; col++) {
				for (int i = 0; i < 3; i++) {
					if (picture[i][row][col].empty() || picture[i][row][col].find(*current) == picture[i][row][col].end()) {
						picture[i][row][col].emplace(*current, 1);
						current++;
						/*max[i][row][col].first = *cur_row;
						max[i][row][col].second = 1;*/
						//cur_row++;
					}
					else {
						auto iter = picture[i][row][col].find(*current);
						iter->second++;
						current++;
						/*max[i][row][col].first = max[i][row][col].second > iter->second ? max[i][row][col].first : iter->first;
						max[i][row][col].second = max[i][row][col].second > iter->second ? max[i][row][col].second : iter->second;
						*///cur_row++;
					}
				}
			}
		}
	}
	frame = temp;//用于process
}
void Recovery::process() {
	//统计每一帧每一个像素点的颜色出现次数最多的结果放进res里面
	for (int row = 0; row < height; row++) {
		uchar* current = frame.ptr<uchar>(row);
		for (int col = 0; col < width; col++) {
			for (int i = 0; i < 3; i++) {
				if (res[i][row][col].second==0 || picture[i][row][col].find(*current) == picture[i][row][col].end()) {
					res[i][row][col].first = *current;
					res[i][row][col].second = 1;
					current++;
				}
				else {
					auto iter = picture[i][row][col].find(*current);
					res[i][row][col].first = res[i][row][col].second > iter->second ?res[i][row][col].first : iter->first;
					res[i][row][col].second = res[i][row][col].second > iter->second ? res[i][row][col].second : iter->second;
					current++;
				}
			}
		}
	}
	//把答案放进ans里面
	for (int row = 0; row < height; row++) {
		uchar* cur = ans.ptr<uchar>(row);
		for (int col = 0; col < width; col++) {
			for (int i = 0; i < 3; i++) {
				*cur = res[i][row][col].first;
				cur++;
			}
		}
	}
}
void Recovery::showResult() {
	namedWindow("ans", WINDOW_FREERATIO);
	imshow("ans",ans);
	waitKey(0);
	destroyAllWindows();
}