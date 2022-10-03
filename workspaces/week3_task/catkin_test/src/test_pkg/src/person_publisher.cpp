#include <ros/ros.h>
#include "test_pkg/Person.h"

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "person_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/person_info的topic，消息类型为learning_topic::Person，队列长度10
    ros::Publisher person_info_pub = n.advertise<test_pkg::Person>("/person_info", 10);

    // 设置循环的频率
    ros::Rate loop_rate(1);

    int count = 0;
    while (ros::ok())
    {
        // 初始化learning_topic::Person类型的消息
    	test_pkg::Person person_msg;
		person_msg.name = "Jared";
		person_msg.age  = 19;
		person_msg.gender  = test_pkg::Person::male;
		person_msg.random_number = rand();

        // 发布消息
		person_info_pub.publish(person_msg);

       	ROS_INFO("Publish Person Info: name:%s  age:%d  gender:%d  random_number:%d", 
				  person_msg.name.c_str(), person_msg.age, person_msg.gender,person_msg.random_number);

        // 按照循环频率延时
        loop_rate.sleep();
    }

    return 0;
}
