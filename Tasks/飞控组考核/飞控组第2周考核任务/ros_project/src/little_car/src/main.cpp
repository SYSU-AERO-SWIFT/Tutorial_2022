#include "parser.h"
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <urdf/model.h>

#include <geometry_msgs/Point.h>
#include "controller/car.h"
#include <random>
#include <iomanip>
using namespace std;

class listener{
	private:
	   SVector3 velocity;
	   float yaw;
	public:
	   void callback(const controller::car & msg);
  
};

 void listener::callback(const controller::car & msg){
        velocity={msg.x,msg.y,msg.z};
        yaw=msg.yaw;
        car.set_yaw(yaw);                  //修改小车的方向
        car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新

}


int main(int argc, char** argv) {
	void callback(const geometry_msgs::Point & msg);
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;

	little_car car;//初始化控制对象  小车

    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);

	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */

	car.set_noise_level(0);		   //设置噪声等级
        class listener lstn;   
	ros::Subscriber a=n.subscribe("turn",10,&lstn::callback,&lstn);
    
    return 0;
}




	
