#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/Point.h>
#include <cmath>

#define FREQ 20  // Hz

int main(int argc, char** argv) {
    ros::init(argc, argv, "ctrlPub");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::Point>("/velocity_cmd", 10);
    
    ros::Rate loop_rate(FREQ);
    while (ros::ok()) {
        double t = ros::Time::now().toSec();

        geometry_msgs::Point msg;
        msg.x = 0.005 * sin(t);
        msg.y = 0.005;
        msg.z = 0;
        
        pub.publish(msg);

        loop_rate.sleep();
    }
}
