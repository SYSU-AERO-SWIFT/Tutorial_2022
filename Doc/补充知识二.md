# Linux下编辑文本的工具

Author：@stuynq

Revise：

| 版本 | 说明 |备注|
| ---- | ---- | ---- |
| v0.0.0 | 建立文档 |无|
| v0.0.1 | 添加文本编辑工具的说明 |@stuynq|

## 前言

本文推荐实现在**Linux**上快速、方便的编辑代码，可选用的工具，包括**vim、gedit、visual studio code**。

## 软件/工具 介绍

> **vim：** vim是Linux上的一款文本编辑器，可用于在使用终端时浏览和编辑文本文件；
>
> **gedit：** Linux上的 “记事本” ；
>
> **Visual Studio Code：**vscode可配置自己配置代码编译、debugg的环境，可方便地进行代码的浏览；

## 软件安装/环境配置

安装软件前可先更新一下软件列表

````shell
sudo apt-get update
````

**vim** 安装命令

````
sudo apt-get install vim
````

**gedit** 安装命令

````
sudo apt-get install gedit
````

vscode的安装：首先在Linux环境下到[vscode官网](https://code.visualstudio.com/)下载 .deb 文件，然后在安装包所处的文件夹下启动终端，输入以下命令完成安装
````
sudo dpkg -i [这里是包名.deb]
````
关于vscode的环境配置请参考以下的官方文档，有很详细的介绍，包括GCC、GDB的安装以及配置实例。


## 推荐教程/参考资料

[vscode官方文档](https://code.visualstudio.com/docs/getstarted/userinterface) 

> 在页面的左侧栏选择你需要配置的语言找到相对应的教程。

[vim的使用教程](https://zhuanlan.zhihu.com/p/68111471)

