#include "ros/ros.h"
#include "srv_and_cen/Person.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"qingqiu");
    ros::NodeHandle node_handle;
    ros::ServiceClient client=node_handle.serviceClient<srv_and_cen::Person>("judge");
    ros::Rate rate(1);
    srv_and_cen::Person ai;
    while(ros::ok)
    {
    ai.request.random_float=(rand()%100)/100.0;
    bool flag=client.call(ai);
    if(flag)
    {
        ROS_INFO("The random float number client sends is %.2f",ai.request.random_float);
        if(ai.response.result)
        {
            ROS_INFO("Yes");
        }
        else
        {
            ROS_INFO("No");
        }
    }
    else
    {
        ROS_INFO("Client sends a wrong number");
    }
    rate.sleep();
    ros::spinOnce();
    }
    return 0;
}
