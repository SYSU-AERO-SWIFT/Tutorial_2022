# 基于OpenCV完成考核任务

Author：@Louyf

Revise：@Xiezx

| 版本   | 说明                 | 备注 |
| ------ | -------------------- | ---- |
| v0.0.1 | 参考21年wiki建立文档 |@Louyf|




## 前言
OpenCV (Open Source Computer Vision Library) 是开源的机器视觉和机器学习软件库。目前 OpenCV 发布到 4.6.0 版，但由于我们最终的部署平台是 NVIDIA Jetson TX2，其上部署的 OpenCV 版本是 3.3.1，因此没法用到在这个版本之后推出的功能。
## 软件介绍
OpenCV海纳百川的特性使得它成为了最优秀的图像处理软件库之一，我们将学习如何使用它来从图像中提取信息。
## 软件安装/环境配置
#环境
Ubuntu 18.04 
#依赖
使用包管理器从软件源安装 OpenCV 时会自动处理依赖，至少确保安装了编译系统、cmake、Python 3 或 Python 2。
#安装方式
OpenCV 库提供多种语言的接口，支持最完善的两个是 C++ 和 Python。这里将介绍从软件源安装 OpenCV，如无必要不推荐从源代码开始重新编译。
- Ubuntu 18.04
  - OpenCV with Python
基本上不会用到 Python 版本的 OpenCV，节省空间不装也行。
```shell
# 安装 Python 2 接口
$ sudo apt install python-opencv
# 安装 Python 3 接口
$ sudo apt install python3-opencv
```
验证安装
```shell
# Python 2
$ python
Python 2.7.14+ (default, Feb 6 2018, 19:12:18) 
[GCC 7.3.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import cv2
>>> cv2._version__
'3.2.0'
>>>
```
```shell
# Python 3
$ python3
Python 3.6.4+ (default, Feb 12 2018, 08:25:03) 
[GCC 7.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import cv2
>>> cv2.__version__
'3.2.0'
>>> 
```

  - OpenCV with C++
Ubuntu 18.04 软件源中的 OpenCV 是 2016 年底发布的 3.2.0 版，你甚至不用担心太新导致在 TX2 上用不了。
```shell
$ sudo apt install libopencv-dev
```
验证安装，编写一个简单的程序

display_image.cpp
```shell
#include <iostream>
// OpenCV library headers
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv ) {
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.

    waitKey(0);             // Wait for a keystroke in the window
    return 0;
}
```
编译
```shell
$ g++ display_image.cpp -o display_image `pkg-config --cflags --libs opencv`
```
编译成功后运行查看效果
```shell
$ ./display_image <图片的路径>
```
## 需要掌握的内容
基本的滤波与特征识别
## 推荐教程/参考资料
[OpenCV官方文档](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html)

[B站上比较好的OpenCV教程](https://www.bilibili.com/video/BV1Mv4y1M7gJ?spm_id_from=333.337.search-card.all.click&vd_source=edcefed95842493f34b0dfe837cf5683)
