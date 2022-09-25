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

~~~
cd bin
make
~~~



### 测试程序

~~~
cd bin
./BG_test <视频文件绝对路径>
~~~





