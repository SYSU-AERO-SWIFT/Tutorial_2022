#include "Recovery.h"

void Recovery::process(string readpath) {
	VideoCapture cap(readpath);
	cap >> src;
	dst = Mat(src.size(), src.type());

	//提前记录视频每一帧图片在每一维下的数据规模，用于遍历
	int r = src.rows;
	int c = src.cols;
	int frame_count = 0;
	int frame_pos = 0;

	//统计帧数
	while (true) {
		if (src.empty())
			break;
		frame_count++;
		cap >> src;
	}
	while (frame_pos < 3 * frame_count) {
		cap >> src;
		if (src.empty()) {
			cap.set(CAP_PROP_POS_FRAMES, 0);
			cap >> src;
		}

		//初次进入循环时，对容器内部实例化，保证后续访问有内存分配
		if (frame_pos == 0) {
			for (int i = 0; i < 3; i++) {
				data->push_back({});
				max->push_back({});
				for (int row = 0; row < r; row++) {
					data[i].push_back({});
					max[i].push_back({});
					for (int col = 0; col < c; col++) {
						unordered_map<uchar, int> m;
						pair<uchar, int> p;
						data[i][row].push_back(m);
						max[i][row].push_back(p);
					}
				}
			}
		}

		//遍历每一帧图片的每一个像素点，统计出现次数最多的像素值
		for (int row = 0; row < r; row++) {
			uchar* cur_row = src.ptr<uchar>(row);
			for (int col = 0; col < c; col++) {
				for (int i = 0; i < 3; i++) {
					if (data[i][row][col].empty() || data[i][row][col].find(*cur_row) == data[i][row][col].end()) {
						data[i][row][col].emplace(*cur_row, 1);
						max[i][row][col].first = *cur_row;
						max[i][row][col].second = 1;
						//cur_row++;
					}
					else {
						auto iter = data[i][row][col].find(*cur_row);
						iter->second++;
						max[i][row][col].first = max[i][row][col].second > iter->second ? max[i][row][col].first : iter->first;
						max[i][row][col].second = max[i][row][col].second > iter->second ? max[i][row][col].second : iter->second;
						//cur_row++;
					}
					cur_row++;
				}
			}
		}

		//若帧数过大，则做降帧处理
		if (frame_count > 250) {
			for (int i = 0; i < 20; i++) {
				frame_pos++;
				cap >> src;
			}
		}
		frame_pos++;
	}
	//将统计结果映射到dst中
	for (int row = 0; row < r; row++) {
		uchar* cur_row_dst = dst.ptr<uchar>(row);
		for (int col = 0; col < c; col++) {
			for (int i = 0; i < 3; i++) {
				*cur_row_dst = max[i][row][col].first;
				cur_row_dst++;
			}
		}
	}
}

void Recovery::saveAndShowResult(string savepath) {
	namedWindow("output", WINDOW_FREERATIO);
	imshow("output", dst);
	imwrite(savepath, dst);
	waitKey(0);
	destroyAllWindows();
}