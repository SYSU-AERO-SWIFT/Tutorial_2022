[toc]

# 视觉组第二周考核任务

## 1.使用opencv提取背景

代码思路：通过为每一个像素点创建一个map统计像素点三个通道出现次数最多的值把这个值赋值给最后呈现出来的图片
video1和video2中障碍物有拖动采取降帧方式减小拖动带来重叠部分对结果的影响
大致代码：

```c++
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
	
```

## 2.程序设计链表题

源代码已提交至文件当中，由于没有添加ListNode定义所以g++编译不通过，但已自行编写测试样例并通过测试

## 3.尝试编写makefile文件

通过b站学习基本操作和多文件下如何找到文件。