#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <std_srvs/Trigger.h>
using namespace std;

geometry_msgs::Point vel_drive;
bool pubCommand = true;

/**
 * 服务通信：该例程在F1TENTH仿真环境下，执行/car_command服务，服务数据类型std_srvs/Trigger
 */


// service回调函数，输入参数req，输出参数res
bool commandCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
	pubCommand = !pubCommand;

    // 显示请求数据
    ROS_INFO("Publish velocity command [%s]", pubCommand==true?"Yes":"No");

	// 设置反馈数据
	res.success = true;
	res.message = "Change turtle command state!";

    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_state_publisher");
    ros::NodeHandle n;

    // 创建一个名为/car_command的server，注册回调函数commandCallback
    ros::ServiceServer command_server = n.advertiseService("/car_command", commandCallback);

	// 创建一个Publisher，发布名为/drive的topic，geometry_msgs::Point消息类型，队列长度10
	ros::Publisher pub_drive = n.advertise<geometry_msgs::Point>("/drive", 10);

    // 循环等待回调函数
    ROS_INFO("Ready to receive car command.");

	// 设置循环的频率
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		// 查看一次回调函数队列
    	ros::spinOnce();
		
		// 如果为true，则发布速度指令, 否则停止
		if(pubCommand)
		{
			vel_drive.y = 0.002;
			pub_drive.publish(vel_drive);
		}
		else
		{
			vel_drive.y = 0.0;
			pub_drive.publish(vel_drive);
		}

	    loop_rate.sleep();
	}

    return 0;
}

