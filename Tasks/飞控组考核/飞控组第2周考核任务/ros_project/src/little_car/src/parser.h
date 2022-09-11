#ifndef __PARSER_H
#define __PARSER_H
#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
typedef struct
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
}SVector3;
class little_car
{
	private:
		SVector3 _velocity;	 //小车速度
		SVector3 _position;  //小车位置
		float _yaw = 0.0;	 //小车的偏航角
		tf::TransformBroadcaster broadcaster;//坐标变换广播
		sensor_msgs::JointState joint_state;
		int _noise_level = 0;
		float _noise[5]={0,0.02,0.04,0.05,0.1};
		geometry_msgs::TransformStamped odom_trans;
		geometry_msgs::Point _pub_position; //小车位置（用来pub的）
		/*test*/
		geometry_msgs::TransformStamped car_trans;
		/*****/
		void add_noise();		//添加噪声
		void update_position(); //更新位置
	public:
		ros::Publisher joint_pub;
		ros::Publisher pos_pub;	//小车位置信息发布者
		void set_noise_level(int level);//设置噪声等级
		little_car();			//构造函数
		SVector3 get_velocity();	//获取小车速度信息
		SVector3 get_position();	//获取小车位置信息
		void set_velocity(SVector3 velocity);//设置小车的速度 
		void set_yaw(float yaw);	//设置小车方向
		void update_();			//小车状态更新
		int move_forward();	//前进函数
		


};




#endif
