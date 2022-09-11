#include "ros/ros.h"
#include "pack1/test.h"
using namespace ros;

void Callback(const pack1::test::ConstPtr& msg)
{
	ROS_INFO("get %d\n",msg->num);
}

int main(int argc, char **argv){
	init(argc,argv,"subscriber");
	NodeHandle n;
	ROS_INFO("ready");
	Subscriber audience=n.subscribe("/topic",10,Callback);
	spin();
	return 0;
}

