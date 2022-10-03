#include <ros/ros.h>
#include "myPackage/Rand.h"

#include <random>
#include <time.h> 
#define RN 9999

int main(int argc, char **argv) {
    ros::init(argc, argv, "randClient");
    ros::NodeHandle n;
    srand(time(0));

    ros::service::waitForService("/randJudge");
    ros::ServiceClient clt = n.serviceClient<myPackage::Rand>("/randJudge");

    myPackage::Rand srv;
    srv.request.name = "hyjack";
    srv.request.rand_num = rand()%(RN+1)/(double)(RN+1);;

    ROS_INFO("Call service to judge if %0.6f < 0.5.", srv.request.rand_num);
    clt.call(srv);

    ROS_INFO("Judge result: %s", srv.response.result ? "Yes" : "No");    
}