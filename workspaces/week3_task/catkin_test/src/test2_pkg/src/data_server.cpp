#include <ros/ros.h>
#include "test2_pkg/data.h"

// service回调函数，输入参数req，输出参数res
bool dataCallback(test2_pkg::data::Request  &req,
         			test2_pkg::data::Response &res)
{
    // 显示请求数据
    ROS_INFO("random_float:%f", req.random_float);

	// 设置反馈数据
	if(req.random_float<0.5)
	{
	    res.result = "Yes";
	}
	else
	{
	    res.result = "No";
	}
	return true;
    
}

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "data_server");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个名为/show_data的server，注册回调函数dataCallback
    ros::ServiceServer data_service = n.advertiseService("/show_data", dataCallback);

    // 循环等待回调函数
    ROS_INFO("Ready to show informtion.");
    ros::spin();

    return 0;
}


