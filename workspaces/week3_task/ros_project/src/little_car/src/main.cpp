#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include "robot_state_publisher/car_v.h"
using namespace std;

SVector3 velocity={0.005,0.008,0};

// 接收到订阅的消息后，会进入消息回调函数
void carCallback(const robot_state_publisher::car_v& msg)
{
    velocity.x=msg.v_x;
    velocity.y=msg.v_y;
    velocity.z=msg.v_z;
    return;
    
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	
	


    // 创建一个Subscriber，订阅名为/robot_state_publisher/cmd_vel的topic，注册回调函数carCallback
    ros::Subscriber car_vel_sub = n.subscribe("/robot_state_publisher/cmd_vel", 10, carCallback);

    // 循环等待回调函数
    
	//spin()循环查看队列中有没有信息，如果有的话就调用poseCallback

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    ros::Rate loop_rate(20);
	//SVector3 velocity={0,0.008,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0;
    while (ros::ok()) {
		yaw -= 0.004;
		car.set_yaw(yaw); 		   //修改小车的方向
		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
        if(velocity.x>=0.008) break;
    }


    return 0;
}

