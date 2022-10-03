#include <ros/ros.h>
#include "practice/Person.h"

void personInfoCallback(const practice::Person::ConstPtr& msg)
{
	ROS_INFO("Subscribe Person Info: name:%s age:%d sex:%d",
		msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "subscriber");
	
	ros::NodeHandle n;
	
	ros::Subscriber info_sub = n.subscribe("/info", 10, personInfoCallback);
	
	ros::spin();
	
	return 0;
}
