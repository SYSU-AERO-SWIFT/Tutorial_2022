## 视频背景还原器模块

- Author: hyjack-00
- Revised: hyjack-00
- Date: 2022-09-25
- Version: 1.0.0
- Abstract: 在 C++ opencv 下基于前景忽略的视频背景还原器

### Functions:

在理想条件（视频背景不运动）下，对存在运动前景遮挡的视频进行背景提取

### Interfaces:

```cpp
// 输入视频本地地址，读入视频
void readVideo(string filePath);

// 对图像进行背景提取处理
void process();

// 展示最终背景，以及处理耗时
void showResult();
```

### Depend Libraries:

- 依赖 opencv

### Testing:

在项目文件夹 `./bin/demo` 为默认测试程序，直接在项目文件夹执行命令 `make` 即可编译。

在项目文件夹执行视频背景提取：

```shell
./bin/demo <video path>
```

提供的三个测试样本还原结果已保存在 `./result` 中。

