# report_wk_3

## 功能包

- 创建工作区文件夹 `catkin_ws/` 
- 创建功能包 `myPackage`

### 话题 topic

- 实现简单自定义消息 `Chat.msg` ，其中 num 域定义为 0 到 1 的随机浮点数

  ```
  string name 
  
  float64 num
  uint8 month
  uint8 day
  ```

- 编写自定义消息的**随机**信息发布节点 `talker`，与信息订阅节点 `listener`，并实现二者通信：

  - talker

    ```
    [ INFO] [1664684965.477056370]: Published chat
    [ INFO] [1664684965.577511012]: Published chat
    [ INFO] [1664684965.677424155]: Published chat
    ```

  - listener

    ```
    [ INFO] [1664684965.477236633]: Chat recieved [num:0.829000, name:hyjack, date:10.2]
    [ INFO] [1664684965.577556720]: Chat recieved [num:0.503000, name:hyjack, date:10.2]
    [ INFO] [1664684965.677512456]: Chat recieved [num:0.019000, name:hyjack, date:10.2]
    ```

### 服务 service

- 实现简单自定义服务 `Rand.srv`

  ```
  string name
  
  float64 rand_num
  ---
  uint8 result
  ```

- 编写服务端节点 `randServer` 与客户端节点 `randClient` ，实现二者通信并完成任务

  - client

    ```\
    ╰─ rosrun myPackage randClient
    [ INFO] [1664695744.144414267]: Call service to judge if 0.929600 < 0.5.
    [ INFO] [1664695744.145926331]: Judge result: No
    ```

  - server

    ```
    ╰─ rosrun myPackage randServer 
    [ INFO] [1664695740.346559059]: Ready for random Judge
    [ INFO] [1664695744.145713753]: Recieve random num 0.929600 >= 0.5
    ```

### launch 启动

```xml
<launch>
    <node pkg="myPackage" type="talker" name="t1" output="screen" />
    <node pkg="myPackage" type="listener" name="l1" output="screen" />

    <node pkg="myPackage" type="randServer" name="rSrv" output="screen" />
    <node pkg="myPackage" type="randClient" name="rClt" output="screen" />

</launch>
```



## PCL 提取目标平面





## 附加题

### 编写launch文件来启动节点

`little/launch/mode.launch` 文件中添加下面一行

```xml
	<node pkg="little_car" type="little_car_node" name="car" output="screen"/>
```

并在 `src/main.cpp` 主循环中添加

```cpp
SVector3 pos = car.get_position();
ROS_INFO("Car position [x:%0.6f y:%0.6f z:%0.6f]", pos.x, pos.y, pos.z);
```

执行以启动节点，终端输出小车运动实时位置信息

```shell
╰─ roslaunch launch/model.launch 
...
[ INFO] [1664712745.442586473]: Car position [x:0.000000 y:0.008000 z:0.000000]
[ INFO] [1664712745.459425398]: Car position [x:0.000000 y:0.016000 z:0.000000]
[ INFO] [1664712745.475900621]: Car position [x:0.000000 y:0.024000 z:0.000000]
[ INFO] [1664712745.492688923]: Car position [x:0.000000 y:0.032000 z:0.000000]
[ INFO] [1664712745.509624017]: Car position [x:0.000000 y:0.040000 z:0.000000]
```

### Publisher控制小车运动

创建 `car_control` 功能包，并实现 `ctrlPub` 节点控制小车速度，实现小车转弯、停止。

使用关于 ROS 时钟时间的正弦曲线实现 S 形运动，`ctrlPub.cpp` 主循环如下，易知小车和速度不超过 0.008，且大于 0.005。

```cpp
while (ros::ok()) {
    double t = ros::Time::now().toSec();

    geometry_msgs::Point msg;
    msg.x = 0.005 * sin(t);
    msg.y = 0.005;
    msg.z = 0;

    pub.publish(msg);

    loop_rate.sleep();
}
```

为了实现多线程，需要在 `main.cpp` 中创建 `subscriber` 并在回调函数中进行数据处理，由于回调函数只有一个参数且没有返回值，需要实现为 `little_car` 类的成员函数：

```cpp
void little_car::ctrlCallBack(const geometry_msgs::Point::ConstPtr &msg) {
	SVector3 vel;
	vel.x = msg->x;
	vel.y = msg->y;
	vel.z = msg->z;
	double yaw = -tan(msg->x / msg->y) / 2;

	ROS_INFO("Control velocity [x:%0.6f y:%0.6f z:%0.6f yaw:%0.6f]", vel.x, vel.y, vel.z, yaw);
	set_velocity(vel);
	set_yaw(yaw);
}
```

```cpp
// main.cpp 主循环

	while (ros::ok()) {
        car.update_(); //小车状态更新

		ros::spinOnce();
		loop_rate.sleep();
    }
```

在相关 xml 文件补充节点启动命令：

```xml
	<node pkg="car_control" type="ctrlPub" name="ctrlPub"/>
```







