# 考核报告 - wk 1

- Author: 黄宇杰 @hyjack-00
- Date: 2022-9-11
- Group: 视觉组

> ### wk_1 文件清单
>
> - 考核报告 - wk 1.md
> - hello_world
>   - .gitignore
>   - helloworld.cpp



## 虚拟机安装 Linux 操作系统 *

- 安装 VMware Workstation 16 Pro
- 下载安装 Ubuntu-18.04.6-desktop-amd64，分配磁盘大小 30 GB
- 配置其他内容
  - VMware Tools https://blog.csdn.net/Williamcsj/article/details/121019391
  - IBus 智能拼音输入法 https://www.modb.pro/db/437558

## 学习 Git 与 Github *

- ubuntu 虚拟机内配置 git 并关联 github 账号
- `clone` 获取账户 fork 的考核仓库
- 在本地工作区 Tutorial_2022/workspaces 创建 test.md，成功上传到本地仓库并提交到 github 仓库

## 安装 openCV *

- 前置环境
  - 安装编译系统 build-essential
  - 安装 cmake 3.10.2
- 安装 openCV 3.2.0
- 成功跑通实例程序，显示单张图片

## 学习使用 Vim

- 系统预装的 vim.tiny 不完整，卸载后安装 vim
- 学习 vim 的命令、编辑、末行模式



利用 vim 在 Linux 编写 Hello World 程序并且编译执行通过：

- 在 `Tutorial_2022/workspace` 下创建并编写 helloworld.cpp ：

  ```
  vim helloworld.cpp
  ```

- 具体代码：

  ```cpp
  #include <iostream>
  
  using namespace std;
  
  int main() {
  	cout << "Hello World" << endl;
      return 0;
  }
  ```

- `:wq` 保存并退出

- 在 `Tutorial_2022/workspace` 下，一步编译成可执行文件 

  ```
  g++ helloworld.cpp -o helloworld.out
  ```

- `./helloworld.out`执行文件，顺利输出

  ```
  Hello World
  ```

  
