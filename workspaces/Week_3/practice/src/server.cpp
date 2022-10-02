#include <ros/ros.h>
#include <practice/Float.h>

bool floatCallback(practice::Float::Request  &req, practice::Float::Response  &res)
{
	if(req.ran < 0.5)
		res.result = 1;
	else
		res.result = 0;
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "server");
	
	ros::NodeHandle n;
	
	ros::ServiceServer server = n.advertiseService("/show_float", floatCallback);
	
	ros::spin();
	
	return 0;
}
