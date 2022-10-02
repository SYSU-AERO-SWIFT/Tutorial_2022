/**
 * 该例程将发布/robot_state_publisher/cmd_vel话题，自定义消息类型robot_state_publisher::car_v

 */
 
#include <ros/ros.h>
#include "robot_state_publisher/car_v.h"


int main(int argc, char **argv)
{
	// ROS节点初始化
	ros::init(argc, argv, "robot_state_publisher");

	// 创建节点句柄
	ros::NodeHandle n;

	// 创建一个Publisher，发布名为/robot_state_publisher/cmd_vel的topic，消息类型为robot_state_publisher::car_v，队列长度10（即向ROS Master注册节点信息）
	ros::Publisher car_vel_pub = n.advertise<robot_state_publisher::car_v>("/robot_state_publisher/cmd_vel", 10);

	// 设置循环的频率
	ros::Rate loop_rate(20);

	int count = 0;
	robot_state_publisher::car_v msg;
	msg.v_x=0.005;
	msg.v_y=0.005;
	msg.v_z=0;
	while (ros::ok())
	{
	    // 初始化geometry_msgs::Twist类型的消息
		msg.v_x+=0.008;
	    // 发布消息
		car_vel_pub.publish(msg);
		ROS_INFO("Publsh car velocity command[%0.2f m/s, %0.2f m/s, %0.2f m/s]", 
				msg.v_x, msg.v_y,msg.v_z);

	    // 按照循环频率延时
	    loop_rate.sleep();
	}

	return 0;
}
