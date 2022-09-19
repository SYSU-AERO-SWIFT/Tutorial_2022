#include"ros/ros.h"
#include"controller/car.h"
#include<stdlib.h>
using namespace ros;

int main(int argc, char **argv){
	ros::init(argc, argv, "publisher");
	ros::NodeHandle n;
	ros::Publisher broadcast=n.advertise<controller::car> ("turn",10);
	controller::car msg;
	ros::Rate loop(20);
	while(ros::ok()){
	msg.y=0.008
	msg.yaw+=0.01;
	broadcast.publish(msg1);
	loop.sleep();
	}
        ROS_INFO("stop");
	return 0;}


