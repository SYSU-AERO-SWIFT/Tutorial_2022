#include"ros/ros.h"
#include"pack2/test.h"
#include"stdlib.h"
using namespace ros;

int main(int argc, char** argv){
        init(argc,argv,"client");

        NodeHandle n;

        service::waitForService("/link");

        ServiceClient appliant=n.serviceClient<pack2::test>("/link");

        pack2::test x;

        while(1){
        x.request.ran= rand()*1.0/(RAND_MAX*1.0);
        if(appliant.call(x))ROS_INFO("%f,Yes\n",x.request.ran);
        else ROS_INFO("%f,No\n",x.request.ran);}

        return 0;
}

