# 飞控组第三周考核环境配置

Author：@LinHuangnan

Revise：

| 版本 | 说明 |备注|
| ---- | ---- | ---- |
| v0.0.0 | 建立文档 |无|
| v0.0.1 |  | |

## 软件安装

### DJI Assistant 2
DJI Assistant 2是一款无人机调参软件，可以快速的对大疆的无人机产品进行参数的调节，也可帮助用户进行产品固件的更新。

#### [下载地址](https://www.dji.com/cn/downloads/softwares/assistant-dji-2)

<div align=center><img width="600"  src="./image/4.jpg"/></div>

## 硬件介绍

### 妙算Manifold-2C
Manifold2是DJI为OSDK开发者打造的第二代微型机载计算机，Manifold2预装Ubuntu16.04操作系统，

- 用户名：dji
- 密码：dji

Manifold2预装了如下软件

<div align=center><img width="600"  src="./image/1.jpg"/></div>

更多详细信息参考[Manifold2用户手册](./doc)

### N3飞控

作为NAZA飞控系列的最新一代产品，N3多旋翼飞控系统采用DJI 大疆最新的控制导航算法。N3飞行控制系统包含主控器（内置双IMU、数据记录仪和气压计），GNSS-Compass模块，电源管理模块（PMU）和LED模块。

更多详细信息参考[N3飞控用户手册](./doc)

## 模拟器仿真
### 0、安装依赖软件（已配置好，此步可省略）
从Github 上获取DJI Onboard SDK，并在DJI Onboard SDK 目录下使用如下命令安装DJI Onboard SDK

```shell
mkdir build 
cd build 
cmake.. 
sudo make -j7 install
```

### 1、创建工作空间
1.1 创建ROS工作空间

```shell
mkdir tasks
cd tasks
mkdir src
```

1.2 将Onboard-SDK-ROS-3.7.0文件夹下的dji_sdk和dji_sdk_demo放到src文件夹下

[Onboard-SDK-ROS-3.7.0下载地址](./package)

1.3 打开终端，进入tasks目录

### 2、编译代码

```shell
catkin_make
```

### 3、配置sdk.launch文件

sdk.launch需要APPID和App Key两个信息。这就需要先在developer上新建一个app来获取

<div align=center><img width="800"  src="./image/9.jpg"/></div>

### 4、硬件连接
- cp210x连接妙算与N3
<div align=center><img width="500"  src="./image/8.jpg"/></div>

- 查看串口，修改对应的sdk.launch文件

```shell
dmesg
```

- 遥控器对频

- 打开`DJI Assitant 2`

- 通过数据线将N3飞控的LED模块与装有`DJI Assitant 2`的电脑连接

<div align=center><img width="300"  src="./image/6.jpg"/></div>


- 此时看到绿灯慢闪，表明飞行器状态正常，可以起飞

### 5、运行示例程序
- 选择N3多旋翼飞行控制系统
<div align=center><img width="300"  src="./image/3.jpg"/></div>

- 使能SDK API
<div align=center><img width="600"  src="./image/5.jpg"/></div>

- `DJI Assitant 2`配置：机架类型选择四旋翼，遥控器选择SBUS，电池选择6S，固件选择V1.7.6.0，波特率选择921600

- 打开模拟器，开始仿真
<div align=center><img width="600"  src="./image/7.jpg"/></div>

- 运行大疆主节点

```shell
roslaunch dji_sdk sdk.launch
```

- 运行程序

```shell
rosrun dji_sdk_demo demo_flight_control
```

## 实际飞行

### 妙算联网
- 安装网卡驱动

```shell
cd RTL8812AU_Linux
chmod 777 install.sh
./install.sh
```

- 手机开热点，PC和妙算连接同一个手机热点，PC远程控制妙算

- 在妙算的命令行输入如下命令，查看ip地址
```shell
ifconfig
```

### 远程控制
- 打开Windows PowerShell，输入如下命令，建立远程连接
```shell
ssh dji@...    (其中...为上一步的ip地址)
```

### 分屏功能介绍
#### 在妙算中使用sudo apt-get install screen安装screen工具
#### 如何使用screen
- 输入命令screen使用工具
- 上下分屏：ctrl+a 再按shift+s
- 切换屏幕：ctrl+a 再按tab键
- 新建一个终端：ctrl+a 再按c
- 关闭一个终端：ctrl+a 再按x


