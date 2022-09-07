#include "ros/ros.h"
#include "srv_and_cen/Person.h"

bool call_back(srv_and_cen::Person::Request &rq,srv_and_cen::Person::Response &res)
{
    float num=rq.random_float;
    if(num>=1.0||num<=0.0)
    {
        ROS_INFO("The number exceeds the limit");
        return false;
    }
    ROS_INFO("Server has received a num %.2f",num);
    if(num<0.5)
    {
        res.result=true;
    }
    else 
    {
        res.result=false;
    }
    ROS_INFO("The result Server sends back is %d",res.result);
    return true;
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"huati");
    ros::NodeHandle node_hanle;
    ros::ServiceServer server=node_hanle.advertiseService("judge",call_back);
    ROS_INFO("Server begins");
    ros::spin();
    return 0;
}
