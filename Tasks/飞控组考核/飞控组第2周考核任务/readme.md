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

[bilibili 网课资源](https://www.bilibili.com/video/BV1zt411G7Vn?from=search&seid=4645403767351408067&spm_id_from=333.337.0.0)。

**本周任务：**

1. 编写 ROS launch 文件并用 `roslaunch` 启动节点。
2. 利用提供的小车模型和源码，模仿源码并在源码的基础上修改，试着实现小车的转弯、停止，并尝试使用 `Publisher` 来发布指令来控制小车的方向和速度。详细要求请见 [任务说明](https://github.com/SYSU-AERO-SWIFT/tutorial_2021/blob/main/tasks/week3/task3_description.md)
3. 让小车走一个 S 形（注意，我们在小车的行走中将加上噪声，你可能需要使用到PID控制）
4. 提交时请使用 `.gitignore` 忽略追踪中间文件（`build/`、`devel/`等）。

**特殊说明：**
  大疆OSDK的任务要求已经更改到了第三周，请大家到第三周的文档查看。

**评分标准：**

| 评分项                        | 分值 |
| ----------------------------- | ---- |
| 编写launch文件来启动节点      | 50分 |
| 实现通过Publisher控制小车运动 | 50分 |
| 让小车走S形（1级噪声）         | 100分 |

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
