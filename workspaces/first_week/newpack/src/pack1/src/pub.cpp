#include"ros/ros.h"
#include"pack1/test.h"
#include<stdlib.h>
using namespace ros;

int main(int argc, char **argv){
	init(argc, argv, "publisher");
	NodeHandle n;
	Publisher broadcast=n.advertise<pack1::test> ("/topic",10);
	pack1::test msg1;
	Rate loop(10);
	while(1){
	msg1.num=rand();
	broadcast.publish(msg1);
	loop.sleep();
	}
        ROS_INFO("stop");
	return 0;}


