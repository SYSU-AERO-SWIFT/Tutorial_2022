#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>

using namespace std;


int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;

	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	ros::Subscriber vel_sub = n.subscribe("/velocity_cmd", 10, &little_car::ctrlCallBack, &car);
	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */

    ros::Rate loop_rate(60);
	SVector3 velocity={0,0.008,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级

    while (ros::ok()) {
        car.update_(); //小车状态更新

		SVector3 pos = car.get_position();
		ROS_INFO("Car position [x:%0.6f y:%0.6f z:%0.6f]", pos.x, pos.y, pos.z);

		ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}

