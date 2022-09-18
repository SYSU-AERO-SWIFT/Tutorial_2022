#include "parser.h"
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <urdf/model.h>
#include <math.h>
#include <geometry_msgs/Point.h>
#include "controller/car.h"
#include <random>
#include<dynamic_reconfigure/server.h>
#include<little_car/PIDConfig.h>
#include <iomanip>
#include "pid.h"
using namespace std;

pid_parm parm={0.014,0.01,0.01};

void callback( little_car::PIDConfig &Config,uint32_t level){
	parm.kp=Config.P;
	parm.ki=Config.I;
	parm.kd=Config.D;}


class listener{
	private:
	   SVector3 velocity;
	   float yaw;
	public:
	   pid_compensate pid;
	   SVector3 position;
           pid_state a,b;
	   l_car* car; 
	   void callback(const controller::car & msg);
           void PidFix(const geometry_msgs::Point &msg);
};

 void listener::callback(const controller::car & msg){
        yaw=msg.yaw;
	velocity={msg.x+pid.x,msg.y+pid.y,0};
	position.x +=msg.x;
	position.y +=msg.y;
        car->set_yaw(yaw);                  //修改小车的方向
        car->set_velocity(velocity);//设置小车速度
        car->update_();//小车状态更新
        ROS_INFO("%f,%f,%f",msg.yaw,position.x,position.y);
}

 void listener::PidFix(const geometry_msgs::Point &msg){
         pid_compensate* m=&pid;
         a.actual=msg.x;
	 b.actual=msg.y;
	 a.target=position.x;
	 b.target=position.y;
	 a=PidElement(parm,a);
	 b=PidElement(parm,b);
	 pid=PidVector(a,b);
 }


int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    class listener lstn;
    lstn.position={0,0,0};
    lstn.pid={0.0,0.0};
    lstn.a.time_delta=lstn.b.time_delta=0.05;
    lstn.a.integral=lstn.b.integral=0;
    lstn.a.previous_error=lstn.b.previous_error=0;
    l_car car;//初始化控制对象  小车
    lstn.car=&car;
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);

    car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
    car.set_noise_level(1);		   //设置噪声等级
    ros::Subscriber a=n.subscribe("turn",10,&listener::callback,&lstn);

    ros::NodeHandle m;
    ros::Subscriber pid=m.subscribe("car_position",10,&listener::PidFix,&lstn);    
    dynamic_reconfigure::Server<little_car::PIDConfig> Server;
    dynamic_reconfigure::Server<little_car::PIDConfig>::CallbackType PIDparameter;
    //PIDparameter=boost::bind(&callback,_1,_2);
    //Server.setCallback(PIDparameter);

    ros::MultiThreadedSpinner s(3);
    ros::spin(s); 
    return 0;
}




	
