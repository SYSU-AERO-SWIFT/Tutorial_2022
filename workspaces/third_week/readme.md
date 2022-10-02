# 第三周考核

<font color="#dd0000"><font size="6"> WARNING：本次任务修改了源码对应的头文件，请务必将dji_sdk_demo/include中的同名头文件替换为库中头文件 </font></font><br />

## 说明
* 任务成果展示在`workspace/third_week`中的`simulator.mp4`，为模拟器飞行视频

* 上述文件夹中的`msgs.bag`为`rosbag`所记录的信息，包含实时位置和速度信息

* 余下部分将详细解释cpp文件中所写的控制代码


## 代码

  在任务要求中分有两个要求

    编写一个发布者以一定频率发布目标位置，并控制无人机接近这个目标点，
    设定两个固定点(它们之间距离适当即可)，控制无人机围绕这两个目标点飞行
 
  将集成到一次飞行中解决，

### **控制**

  首先实际操控的部分，我们设置了三个控制`publisher`

  ```
  ctrlPosYawPub = nh.advertise<sensor_msgs::Joy>("dji_sdk/flight_control_setpoint_generic", 10);
  ctrlPosition = nh.advertise<sensor_msgs::Joy>("dji_sdk/flight_control_setpoint_ENUposition_yaw", 10);
  ctrlBrakePub = nh.advertise<sensor_msgs::Joy>("dji_sdk/flight_control_setpoint_ENUvelocity_yawrate", 10);
```
根据消息类型，后两个发出的指令为定点飞行的位置控制；而第一个为自定义控制类型，在后续`mission.step2()`中我们将其控制类型初始化为
```
 uint8_t flag = (DJISDK::VERTICAL_POSITION |
                  DJISDK::HORIZONTAL_VELOCITY |
                  DJISDK::YAW_RATE |
                  DJISDK::HORIZONTAL_GROUND |
                  DJISDK::STABLE_ENABLE);
```
即水平速度和角速度控制，这是针对第二个环绕任务所设，为了使路线与速度平滑，我们将两个虚设点视为椭圆的焦点，路线视为以两个点为焦点的椭圆。

由于位置控制模式在曲线运动中略显僵硬，因此我们牺牲了一部分的位置精确，转为用速度控制，具体实现方式我们后面仔细说明。

###  **规划**

我们主要通过`void gps_callback(const sensor_msgs::NavSatFix::ConstPtr& msg)`回调函数来进行任务规划，首先对于任务1 ，进行初始化，
```
square_mission.reset();
square_mission.start_gps_location = current_gps;
square_mission.start_local_position = current_local_pos;
square_mission.setTarget(30, 0, 0, -90);
square_mission.state = 1;
ROS_INFO("##### Start route %d ....", square_mission.state);
```
然后进入`mission.step1()`实行定点靠近,为demo中最原始的代码，不再赘述，重点来看任务2

任务1完成后进入`mission.step2()`

```
xCmd = -10*sin(tInRad);

yCmd = 3*cos(tInRad);

zCmd = start_local_position.z + target_offset_z;

yawrate= 0.5;
```
其中`t`是在头文件中自己定义的计时器，每进入一次回调就会加1，因此不难看出，`xCmd`和`yCmd`是椭圆关于`t`的参数方程的x与y方向的导数，即速度；为确保机头始终沿切线方向，我们求椭圆的二阶导并作为`yawrate`,即机身的角速度，然后可以实现围绕焦点飞行。

```
controlPosYaw.axes.push_back(2*xCmd);
controlPosYaw.axes.push_back(2*yCmd);
controlPosYaw.axes.push_back(zCmd);
controlPosYaw.axes.push_back(yawrate);
controlPosYaw.axes.push_back(flag);
ctrlPosYawPub.publish(controlPosYaw);
```
任务2的停止条件为绕圈30秒，即
```
if(t>1500)break_counter=1;    //发布频率为50Hz
```

然后机体悬停。


以上为本次任务全部解释。