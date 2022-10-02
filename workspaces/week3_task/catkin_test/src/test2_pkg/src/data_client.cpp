#include <ros/ros.h>
#include <cstdlib>
#include <ctime>
#include "test2_pkg/data.h"

int main(int argc, char** argv)
{
    // 初始化ROS节点
	ros::init(argc, argv, "data_client");

    // 创建节点句柄
	ros::NodeHandle node;

    // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
	ros::service::waitForService("/show_data");
	ros::ServiceClient data_client = node.serviceClient<test2_pkg::data>("/show_data");

    // 初始化test2_pkg::data的请求数据
	test2_pkg::data srv;
	srand (static_cast <unsigned> (time(0)));
	srv.request.random_float = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


    // 请求服务调用
	ROS_INFO("Call service to show data[random_float:%f]", srv.request.random_float);

	data_client.call(srv);
	// 显示服务调用结果
	ROS_INFO("Show data result : %s", srv.response.result.c_str());

	return 0;
};


