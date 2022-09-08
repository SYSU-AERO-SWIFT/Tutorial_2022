#include "ros/ros.h"
#include "pub_and_sub/Person.h"
#include <iostream>

std::string rand_str(const int len)  
{
    std::string str;                
    char c;                     
    int idx;                    
    for(idx = 0;idx < len;idx ++)
    {
        c = 'a' + rand()%26;
        str.push_back(c);       
    }
    return str;                
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"info");
    ros::NodeHandle node_handle;
    ros::Publisher pub=node_handle.advertise<pub_and_sub::Person>("topic",10);
    pub_and_sub::Person person;
    ros::Rate rate(1);
    while(ros::ok)
    {
        person.name=rand_str(5);
        person.age=rand()%100;
        person.height=1.0+(rand()%100)/100.0;
        pub.publish(person);
        ROS_INFO("The topic you publish is \nname:%s\nage:%d\nheight:%.2f",person.name.c_str(),person.age,person.height);
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
