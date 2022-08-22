# 基于ROS完成考核任务

Author：@ma-h-m

| 版本 | 说明 |备注|
| ---- | ---- | ---- |
| v0.0.0 | 建立文档 |无|
| v0.0.1 | 上传初版教程 |@ma-h-m|

## 前言

ROS是飞控组主要工作平台。[大疆OSDK](https://developer.dji.com/cn/onboard-sdk/)是空队飞控目前使用的工具。为了更好阅读代码，这里要求大家学习ROS与c++编程，对于ROS与python不做要求。

开发环境为Linux，推荐安装虚拟机或双系统。

## 工具介绍
[ROS](https://www.ros.org/about-ros/) (Robot Operating System) 是一套用来方便开发机器人软件的开源框架。
## 软件安装/环境配置
* 请大家安装 ROS 完成考核，这里 ROS 指的是经典版即 ROS 1，而非正在活跃发展中的 [ROS 2](https://index.ros.org/doc/ros2/)。
### Ubuntu
跟随官方教程即可

Unbuntu 20.04请参考[Ubuntu install of ROS Noetic](http://wiki.ros.org/noetic/Installation/Ubuntu), Untunbu 18.04请参考[Ubuntu install of ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)

### Manjaro (Arch Linux)
ROS 并不包含在 Arch 的官方软件源中，Melodic 在 AUR 中提供实验性支持，参考[官方 Arch 教程](http://wiki.ros.org/melodic/Installation/ArchLinux)。

AUR helper 建议使用 [yay](https://github.com/Jguer/yay)，安装 [ros-melodic-desktop-full](https://aur.archlinux.org/packages/ros-melodic-desktop-full) 这个 meta-package，其中包括 ROS 基本库、可视化工具、模拟器等所有 ROS 内容。建议修改 makepkg.conf 开启多线程编译提高速度。


* 推荐使用Unbuntu 18.04，与无人机搭载的妙算系统相同，同时社区较为成熟，大量经验可以借鉴。
* 如果ROS安装中出现网络问题，可以考虑更换清华源，参考[ros安装配置为清华源（镜像）方法步骤](https://blog.csdn.net/lxj362343/article/details/120213070)
## 需要掌握的内容

跟随[ROS Tutorials](http://wiki.ros.org/ROS/Tutorials) 即可🙃。

若感觉该教程过于抽象，可以参考下方b站网课资源。

## 推荐教程/参考资料
[ROS官方文档](http://wiki.ros.org/cn)

[MOOC-ROS教程](https://www.icourse163.org/course/ISCAS-1002580008)

[bilibili 网课资源](https://www.bilibili.com/video/BV1zt411G7Vn?from=search&seid=4645403767351408067&spm_id_from=333.337.0.0)
