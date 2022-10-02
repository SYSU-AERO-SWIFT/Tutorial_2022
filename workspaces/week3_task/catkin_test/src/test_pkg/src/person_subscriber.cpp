#include <ros/ros.h>
#include "test_pkg/Person.h"

// 接收到订阅的消息后，会进入消息回调函数
void personInfoCallback(const test_pkg::Person::ConstPtr& msg)
{
    // 将接收到的消息打印出来
    ROS_INFO("Subcribe Person Info: name:%s  age:%d  gender:%d  random_number:%d", 
			 msg->name.c_str(), msg->age, msg->gender, msg->random_number);
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "person_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Subscriber，订阅名为/person_info的topic，注册回调函数personInfoCallback
    ros::Subscriber person_info_sub = n.subscribe("/person_info", 10, personInfoCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}
