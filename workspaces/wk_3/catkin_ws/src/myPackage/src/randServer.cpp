#include <ros/ros.h>
#include "myPackage/Rand.h"

ros::Publisher pub;

bool randCallBack(myPackage::Rand::Request &req, myPackage::Rand::Response &res) {
    if (req.rand_num < 0.5) {
        res.result = 1;
        ROS_INFO("Recieve random num %0.6f < 0.5", req.rand_num);
    }
    else {
        res.result = 0;
        ROS_INFO("Recieve random num %0.6f >= 0.5", req.rand_num);
    }

    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "randServer");
    ros::NodeHandle n;

    ros::ServiceServer cmd_server = n.advertiseService("/randJudge", randCallBack);

    ROS_INFO("Ready for random Judge");
    ros::spin();
}   