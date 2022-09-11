# 视觉组第一周任务

Author: @Chasers0205



## **任务一：完成必学内容**

### 1.安装Linux操作系统

首先安装搭载平台VMware Workstation并激活，接着下载.iso镜像文件，然后按照步骤创建并安装新的虚拟机，完成安装后如图所示。

![image-20220910193403751](https://github.com/Chasers0205/Tutorial_2022/edit/main/Tasks/视觉组考核/视觉组第1周考核任务/image-20220910144536872.png)


### 2.学习 Git，熟悉 GitHub 的使用：使用 git 和 GitHub 完成考核任务

- `fork` 在考核仓库右上角点击Fork按钮，完成后就成功地将考核仓库拷贝了一份作为自己的部分。

![image-20220910144536872](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220910144536872.png)

- `clone`  将Github中的远程仓库克隆到自己本地电脑中。

![image-20220910145158590](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220910145158590.png)

#出现问题：clone过程中出现"Failed to connect to github.com port 443: Timed out".

#解决方法：在https://www.ipaddress.com/查找github.com以及github.global.ssl.fastly.net的域名，然后在hosts文件最后添加内容：

（hosts文件路径：C:\Windows\System32\drivers\etc）

```
#GitHub Start
140.82.113.3 github.com
185.199.111.153 assets-cdn.github.com
203.208.39.104 documentcloud.github.com
66.249.89.104 gist.github.com
185.199.110.154 help.github.com
13.112.159.149 nodeload.github.com
66.249.89.104 raw.github.com
140.82.114.18 status.github.com
203.208.39.99 training.github.com
52.69.186.44 www.github.com
151.101.1.194 github.global.ssl.fastly.net
151.101.65.194 github.global.ssl.fastly.net
151.101.129.194 github.global.ssl.fastly.net
151.101.193.194 github.global.ssl.fastly.net
185.199.109.133 avatars0.githubusercontent.com
185.199.110.133 avatars1.githubusercontent.com
#GitHub End
```

- `commit` 将自己在本地创建或者修改的代码或文件提交到本地仓库。

![image-20220910202406731](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220910202406731.png)

- `pull`  将本地仓库的修改提交到远程仓库。
- `pull request` 简称`pr`,在 GitHub 上发送 Pull Request 后，发送过去的 Pull Request 是否被采纳，要由接收方仓库的管理者进行判断。接受pr的过程称为`merge`，进而实现自己的Tutorial_2022仓库和SYSU-AERO-SWIFT的Tutorial_2022仓库内容的同步。

### 3.安装opencv，跑通示例程序。

#操作过程：

a. 使用软件源安装opencv。

````
sudo apt install libopencv-dev
````

b. 验证安装，编写一个简单的程序display_image.cpp。

```
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

c. 编译并运行程序，运行结果如图所示。

```
g++ display_image.cpp -o display_image `pkg-config --cflags --libs opencv`
./display_image /home/chasers/Desktop/mytest/test.jpeg
```

![image-20220910195827562](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220910195827562.png)



## 任务二：在 Linux 编写 Hello World 程序并且编译执行通过

#操作过程:

1.使用源代码安装vim编辑器，C的编译器gcc和C++的编译器g++。

```
sudo apt-get install vim gcc g++
```

2.使用源代码创建目录并打开。

```
mkdir mycode
cd mycode
```

3.使用源代码进入vim编辑程序，输入如下代码（详见week_1_code_1.cpp)，完成后保存并退出。

```
vim hello_world.cpp
```

```
#include <iostream>
using namespace std;
int main()
{
	cout<<"Hello world!"<<endl;
	return 0;
}
```

4.使用源代码编译hello_world.cpp生成可执行文件hello_world。

```
g++ hello_world.cpp -o hello_world
```

5.使用源代码运行可执行文件Prime，结果如图所示。

```
./hello_world
```

![image-20220910193216245](C:\Users\不蒸馒头争口气\AppData\Roaming\Typora\typora-user-images\image-20220910193216245.png)



## 任务三：成功的把工程提交到分支上

略。
