[toc]

## 视觉组第二周考核任务说明

- Author：郑广源
- Revised：郑广源
- Date：2022-09-23
- Version：1.0.0
- Abstract：建立该文档，对本周考核成果进行说明

### 考核问题

本周考核题目为**实现一个简单的背景提取算法**

### 说明

#### 接口功能

该项目中实现了一个类，该模块提供了两个接口：
- process函数实现了读取视频文件和生成提取结果
- saveAndShowResult函数实现了保存和展示提取结果

#### 模块代码

```c++
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
    //读取视频，生成算法结果
	void process(string readpath);
    //保存和展示结果
	void saveAndShowResult(string savepath);
};
```

#### 依赖库

- 依赖openCV
- 依赖C++ 标准库

#### 编译提示

通过工程文件夹中的makefile文件进行编译，*需要将makefile和源文件置于同一个目录下*

#### 测试提示

> $ cd bin

>$ ./test_task

> #输入视频绝对路径 输入图片存储路径