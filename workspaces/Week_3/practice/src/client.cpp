#include <ros/ros.h>
#include <practice/Float.h>
#include<stdlib.h> 
#include<time.h> 

int main(int argc, char** argv)
{
	ros::init(argc, argv, "client");
	
	ros::NodeHandle node;
	
	ros::service::waitForService("/show_float");
	ros::ServiceClient client = node.serviceClient<practice::Float>("/show_float", 10);
	
	ros::Rate loop_rate(1);
	
	while(ros::ok())
	{
		practice::Float fl;
		
		srand ((time(nullptr)));
		fl.request.ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		
		client.call(fl);
		
		std::string end;
		end = fl.response.result == 1 ? "Yes" : "No";
		ROS_INFO("Show  result : %f %s", fl.request.ran, end.c_str());
		
		loop_rate.sleep();
	}
	
	return 0;
}
