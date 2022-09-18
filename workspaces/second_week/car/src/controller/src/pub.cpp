#include"ros/ros.h"
#include"controller/car.h"
#include<stdlib.h>
#include<math.h>
using namespace std;

int main(int argc, char **argv){
	ros::init(argc, argv, "publisher");
	ros::NodeHandle n;
	ros::Publisher broadcast=n.advertise<controller::car> ("turn",10);
	controller::car msg;
	ros::Rate loop(20);
	while(ros::ok()){
	while(msg.yaw<=3.14){
	msg.yaw+=0.01;
	msg.y=0.006*cos(msg.yaw);
	msg.x=-0.006*sin(msg.yaw);
	broadcast.publish(msg);
	loop.sleep();}
	while(msg.yaw>=0){
        msg.yaw-=0.01;
        msg.y=0.004*cos(msg.yaw);
        msg.x=-0.004*sin(msg.yaw);
        broadcast.publish(msg);
        loop.sleep();}
	}
        ROS_INFO("stop");
	return 0;}


