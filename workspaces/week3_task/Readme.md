# Readme

Title Here: ROS基础考核

- Author: 吕捷为
- Revised: 吕捷为
- Date: 2022-10-2
- Version: 1.0.0
- Abstract: ROS的基本操作



## Depend Libraries:

~~~
依赖ROS
~~~



## 任务一：Publisher与Subscriber通信

### 编译提示

* package.xml功能包依赖

~~~
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
~~~

* CMakeLists.txt编译选项

~~~
//在test_pkg下的CMakeLists.txt中
find_package(....... message_generation)    //即在众多的里加上一个

//大概81行处，declare dynamic ......的上面
add_message_files(FILES Person.msg)
generate_messages(DEPENDENCIES std_msgs)

//115行处的CATKIN_DEPENDS前的#号删除，然后在后面加上message_runtime
catkin_package(.......... message_runtime)
~~~

* 配置代码编译规则

~~~
add_executable(person_publisher src/person_publisher.cpp)
target_link_libraries(person_publisher ${catkin_LIBRARIES})
add_dependencies(person_publisher ${PROJECT_NAME}_generate_messages_cpp)

add_executable(person_subscriber src/person_subscriber.cpp)
target_link_libraries(person_subscriber ${catkin_LIBRARIES})
add_dependencies(person_subscriber ${PROJECT_NAME}_generate_messages_cpp)
~~~

* 编译

~~~
cd ~/catkin_test
catkin_make
~~~



### 测试程序

方法一：

~~~
roscore
rosrun test_pkg person_subscriber
rosrun test_pkg person_publisher
~~~

方法二：调用launch

~~~
roslaunch test_pkg test.launch 
~~~



## 任务二：Service与Client通信

### 编译提示

* package.xml功能包依赖

~~~
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
~~~

* CMakeLists.txt编译选项

~~~
//在test2_pkg下的CMakeLists.txt中
find_package(....... message_generation)    //即在众多的里加上一个

//大概81行处，declare dynamic ......的上面
add_service_files(FILES data.srv)
generate_messages(DEPENDENCIES std_msgs)

//115行处的CATKIN_DEPENDS前的#号删除，然后在后面加上message_runtime
catkin_package(.......... message_runtime)
~~~

* 配置代码编译规则

~~~
add_executable(data_server src/data_server.cpp)
target_link_libraries(data_server ${catkin_LIBRARIES})
add_dependencies(data_server ${PROJECT_NAME}_gencpp)

add_executable(data_client src/data_client.cpp)
target_link_libraries(data_client ${catkin_LIBRARIES})
add_dependencies(data_client ${PROJECT_NAME}_gencpp)
~~~

* 编译

~~~
cd ~/catkin_test
catkin_make
~~~



### 测试程序

方法一：

~~~
roscore
rosrun test2_pkg data_client
rosrun test2_pkg data_server
~~~

方法二：调用launch

~~~
roslaunch test2_pkg test2.launch 
~~~



##  任务三：调用PCL库提取目标平面

* 进入文件夹

~~~
cd ~/pcl_test
~~~

* 查看提取前桌面

~~~
pcl_viewer table_scene_lms400.pcd 
~~~

* 查看提取后图像

~~~
pcl_viewer cloud_cluster_0.pcd cloud_cluster_1.pcd cloud_cluster_2.pcd cloud_cluster_3.pcd cloud_cluster_4.pcd
~~~



## 附加题

## 任务一：编写launch文件来启动节点

~~~
roslaunch launch/little_car.launch
~~~

### 任务二：实现通过Publisher控制小车运动

完成，执行上面的launch文件即可看见。

### 任务三：让小车走S形（1级噪声）

未实现

