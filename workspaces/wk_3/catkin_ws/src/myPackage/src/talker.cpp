#include <ros/ros.h>
#include "myPackage/Chat.h"

#include <random>
#define RN 9999

int main(int argc, char **argv) {
    ros::init(argc, argv, "listening");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<myPackage::Chat>("/chat", 10);
    
    ros::Rate loop_rate(10);
    while (ros::ok()) {
        myPackage::Chat chat_msg;
        chat_msg.name = "hyjack";
        chat_msg.month = 10;
        chat_msg.day = 2;
        
        chat_msg.num = rand()%(RN+1)/(double)(RN+1);

        pub.publish(chat_msg);
        ROS_INFO("Published chat");

        loop_rate.sleep();
    }
}