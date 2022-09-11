## 基础考核 - 第二周（9.12-9.18）

Author：@ma-h-m

| 版本 | 说明 |备注|
| ---- | ---- | ---- |
| v0.0.1 | 完成初版文档 |分数分配待定|

**必学内容：**

1. 熟悉 ROS 的基本操作，包括文件架构、通信机制 (`Publisher`, `Subscriber`, `Service`, `Client`, `msgs`)、包的创建、节点、服务器等。
2. 熟悉`roslaunch`的基本使用，进一步了解如何将机器人模型在`.launch`文件中加载到参数服务器上。
3. 熟悉ROS TF包、了解如何在RVIZ中模拟机器人模型的运动。参考资料：[ROS TF包 官方文档]([tf/Tutorials - ROS Wiki](http://wiki.ros.org/tf/Tutorials))，建议阅读一遍官方文档中的`Learning TF`，以把握基本概念。
4. 了解大疆模拟器与妙算的使用。
5. （*选学）了解`urdf`文件、`gazebo`仿真、`xacro`文件。
6. 参考资料：

[ROS官方文档](http://wiki.ros.org/cn)

[MOOC-ROS教程](https://www.icourse163.org/course/ISCAS-1002580008)

[bilibili 网课资源](https://www.bilibili.com/video/BV1zt411G7Vn?from=search&seid=4645403767351408067&spm_id_from=333.337.0.0)。

[DJI OSDK官方文档](https://developer.dji.com/cn/onboard-sdk/).

[【大疆无人机OnboardSDK（一）Assistant2仿真系统搭建】](https://blog.csdn.net/KID_yuan/article/details/102518205)

**特殊说明：**

本周任务将在上一周任务的基础上完成，难度较高，就算不能完成也不必担心。（去年考核时几乎没动ROS这几题QAQ——by ma-h-m）   

可以考虑跳过2——5题，完成第6-7题。

第6题之后的任务需要模拟器与妙算，需要来实验室完成。有任何问题请在考核群内@飞控组成员。这几道题可以在第三周继续完成。

**本周任务：**

1. 编写 ROS launch 文件并用 `roslaunch` 启动节点。
2. 利用提供的小车模型和源码，模仿源码并在源码的基础上修改，试着实现小车的转弯、停止，并尝试使用 `Publisher` 来发布指令来控制小车的方向和速度。详细要求请见 [任务说明](https://github.com/SYSU-AERO-SWIFT/tutorial_2021/blob/main/tasks/week3/task3_description.md)
3. 让小车走一个 S 形（注意，我们在小车的行走中将加上噪声，你可能需要使用到PID控制）
4. 编写一个基于ROS的模拟器对任务七仿真，详细说明[在这里](https://github.com/SYSU-AERO-SWIFT/tutorial_2021/blob/main/tasks/week3/project_description.md)
5. 提交时请使用 `.gitignore` 忽略追踪中间文件（`build/`、`devel/`等）。
6. 尝试大疆OSDK仿真环境。运行djiosdk-flightcontrol-sample程序，具体流程请参照参考资料中最后一项。
7. 修改上题中的样例程序，使得无人机能够围绕两个目标点绕圈飞行。运行结果请截图上传。
**评分标准：**

| 评分项                        | 分值 |
| ----------------------------- | ---- |
| 完成Publisher与Subscriber通信 | 10分 |
| 在通信中使用自己的msgs        | 5分 |
| 编写launch文件来启动节点      | 5分 |
| 完成Service与Client通信       | 10分 |
| 完成动态参数服务器            | 10分 |
| 实现通过Publisher控制小车运动 | 15分 |
| 使用多线程以20Hz的频率控制小车| 15分 |
| 让小车走S形（1级噪声）         | 15分 |
|模拟器|115分|

**怎么运行所提供的小车程序？**

```shell
$ cd ros_project  # 请先确保工程在catkin workspace下
$ catkin_make  
$ source devel/setup.bash
$ roslaunch launch/little_car.launch
```

**Tips:**

1. 多看 ROS wiki 以及使用搜索引擎将有助于你解决大部分问题。
2. 对于源码有疑问，可以在群里发问，我们会在合适的范围内给予解答。
