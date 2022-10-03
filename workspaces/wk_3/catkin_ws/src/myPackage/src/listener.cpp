#include <ros/ros.h>
#include "myPackage/Chat.h"

void chatCallBack(const myPackage::Chat::ConstPtr &msg) {
    ROS_INFO("Chat recieved [num:%0.6f, name:%s, date:%d.%d]",
            msg->num, msg->name.c_str(), msg->month, msg->day);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/chat", 10, chatCallBack);
    
    ros::spin();
}