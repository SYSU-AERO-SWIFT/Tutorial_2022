## 基础考核 - 第三周（9.26-10.2）

**必学内容：**

1. 熟悉 ROS 的基本操作，包括文件架构、通信机制 (`Publisher`, `Subscriber`, `Service`, `Client`, `msgs`)、包的创建、节点、服务器等。
2. 熟练使用检索工具，善于查看官方文档获取资料。
3. 熟练使用 `cmake`。
4. 参考资料：[ROS官方文档](http://wiki.ros.org/cn)、[MOOC-ROS教程](https://www.icourse163.org/course/ISCAS-1002580008)、[bilibili 网课资源](https://www.bilibili.com/video/BV1zt411G7Vn?from=search&seid=4645403767351408067&spm_id_from=333.337.0.0)、[PCL官方教程集合]( https://pcl.readthedocs.io/projects/tutorials/en/master/)、[PCL安装指南](https://pcl.readthedocs.io/projects/tutorials/en/master/#basic-usage)。

**选修内容：**

1. 了解 ROS 常用的可视化调试工具，包括二维的 `rosplot`，三维的 `rviz` 等。

**本周任务：**

1. 编写一个 package，其中包含一个信息发布节点 `Publisher`，和一个信息订阅节点 `Subscriber`。信息发布节点产生随机数据并发布，要求使用自己创建的自定义消息类型，信息订阅节点订阅话题并将数据输出到终端。
2. 编写 ROS launch 文件并用 `roslaunch` 启动节点。
3. 编写 `Service` 和 `Client`，`Client` 产生一个 0 到 1 内的随机浮点数，然后发给 `Service`，`Service` 接受到请求后，判断随机数是否小于 0.5，若是则回应布尔值 1，否则回应 0。`Client` 接收到回应后，先输出产生的随机数，然后输出 `Yes` 或 `No` 到终端。
4. 安装PCL点云处理库，调库实现从官方例程点云中提取目标的平面。

**评分标准：**

| 评分项                        | 分值 |
| ----------------------------- | ---- |
| 完成Publisher与Subscriber通信 | 10分 |
| 在通信中使用自己的msgs        | 5分 |
| 编写launch文件来启动节点      | 5分 |
| 完成Service与Client通信       | 10分 |
| 成功提取目标平面              | 20分 |



```

**Tips:**

1. 多看 ROS wiki 以及使用搜索引擎将有助于你解决大部分问题。
2. 对于源码有疑问，可以在群里发问，我们会在合适的范围内给予解答。

