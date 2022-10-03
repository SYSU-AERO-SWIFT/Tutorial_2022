#include <ros/ros.h>
#include <practice/Person.h>
#include<stdlib.h> 
#include<time.h> 

int main(int argc, char** argv)
{
	ros::init(argc, argv, "publisher");
	
	ros::NodeHandle n;
	
	ros::Publisher info_pub = n.advertise<practice::Person>("/info", 10);
	
	ros::Rate loop_rate(1);
	
	practice::Person person_msg[10];
	person_msg[0].name = "Tom";
	person_msg[0].age  = 18;
	person_msg[0].sex  = practice::Person::male;
	person_msg[1].name = "Jerry";
	person_msg[1].age  = 19;
	person_msg[1].sex  = practice::Person::male;
	person_msg[2].name = "Spike";
	person_msg[2].age  = 20;
	person_msg[2].sex  = practice::Person::male;
	person_msg[3].name = "Tuffy";
	person_msg[3].age  = 1;
	person_msg[3].sex  = practice::Person::unknown;
	person_msg[4].name = "Tyke";
	person_msg[4].age  = 15;
	person_msg[4].sex  = practice::Person::female;
	person_msg[5].name = "Linda";
	person_msg[5].age  = 22;
	person_msg[5].sex  = practice::Person::female;
	person_msg[6].name = "Sarah";
	person_msg[6].age  = 25;
	person_msg[6].sex  = practice::Person::female;
	person_msg[7].name = "Pluto";
	person_msg[7].age  = 30;
	person_msg[7].sex  = practice::Person::male;
	person_msg[8].name = "Charon";
	person_msg[8].age  = 30;
	person_msg[8].sex  = practice::Person::female;
	person_msg[9].name = "Victor";
	person_msg[9].age  = 20;
	person_msg[9].sex  = practice::Person::male;
	
	
	while(ros::ok())
	{
		
		srand(time(nullptr));
		rand();
		int ran = rand() % 10 ;
		info_pub.publish(person_msg[ran]);
		
		ROS_INFO("Publish Person Info: name:%s age:%d sex:%d",
			person_msg[ran].name.c_str(), person_msg[ran].age, person_msg[ran].sex);
				
		loop_rate.sleep();
	}
	
	return 0;
}
