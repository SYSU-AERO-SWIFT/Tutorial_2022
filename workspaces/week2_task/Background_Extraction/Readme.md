# Readme

Title Here: 视频背景提取

- Author: 吕捷为
- Revised: 吕捷为
- Date: 2022-9-25
- Version: 1.0.0
- Abstract: 视频背景提取

### Interfaces:
    void readVideo(string filePath);//读取视频
    void process();//视频处理，即背景提取
    void showResult();//展示提取出的背景
    Mat track(Mat background, Mat frame);追踪移动前景，在视频处理时用到
### Depend Libraries:

~~~
依赖opencv
~~~

### 编译提示

**方法一**

输入

~~~
g++ BG_main.cpp BG_H.h BG_Recovery.cpp -o main `pkg-config --cflags --libs opencv`
~~~

编译完成，生成main执行文件

**方法二**

输入

~~~
make
~~~

调用Makefile文件编译



### 测试程序

在编译好的情况下，输入

~~~
./main <视频文件绝对路径>
~~~

第二个输入作为argv[1]参数输入

### 算法实现流程

本程序同时利用帧差法与背景减法，实现背景提取

1. 读取视频后，首先选用帧差法，将前后两帧转为灰度图后做差，得到两帧的不同点。

2. 得到不同后，利用阈值化处理，放大得到不同的区块。
3. 利用findContours函数找到轮廓后画出前后不同的区域（灰度图）
4. 利用copyTo函数，不将像素值为0的像素点更新到background中，即可以保留像数值为0处的原始像数值
5. 用addWeighted函数，逐步更新背景，最终得到完整背景。

### 可优化的点

在阈值化处理后可以进行腐蚀和膨胀的操作，使得背景的提取更加稳定。

