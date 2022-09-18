#第二周考核任务

## car

这是考核任务中的小车内容，对于已完成的内容

* 使用`publisher`以20Hz发布方向和速度（为自建的msgs），小车节点的`suscriber_1`接收信息实现走S型

* 搭建动态参数器实现PID控制，并在小车中内植`server`进行实时调参
```
dynamic_reconfigure::Server<little_car::PIDConfig> Server;
    dynamic_reconfigure::Server<little_car::PIDConfig>::CallbackType PIDparameter;
    PIDparameter=boost::bind(&callback,_1,_2);
    Server.setCallback(PIDparameter);
```

```
void callback( little_car::PIDConfig &Config,uint32_t level){
	parm.kp=Config.P;
	parm.ki=Config.I;
	parm.kd=Config.D;}
```
* 使用`roslaunch`启动所有节点及`rviz`与`rqt_reconfigure`
   (car/launch/little_car.launch)

* 多线程接收控制消息`\control`和`geometry_msgs`，`geometry_msgs`用以接受实时位置反馈给PID算法修正轨迹，并把补偿量加入速度
```
ros::MultiThreadedSpinner s(3);
    ros::spin(s); 
```
## 注意
* 在源码中（little_car/src/main.cpp)因开启调参`service`rviz中`tf`因未知原因崩溃，所以打了注释，如能赐教，感激不尽
* 环境模拟尚未搭建出，仍在学习搭建`urdf`和调用各个模块，希望可以再给一些时间
