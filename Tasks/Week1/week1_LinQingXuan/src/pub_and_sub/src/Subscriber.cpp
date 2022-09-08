#include "ros/ros.h"
#include "pub_and_sub/Person.h"

void call_back(const pub_and_sub::Person::ConstPtr& person)
{
    ROS_INFO("The topic you subscribe is \nname:%s\nage:%d\nheight:%.2f",person->name.c_str(),person->age,person->height);
}


int main(int argc, char *argv[])
{
    ros::init(argc,argv,"get_topic");
    ros::NodeHandle node_handle;
    ros::Subscriber sub=node_handle.subscribe("topic",10,call_back);

    ros::spin();

    return 0;
}
