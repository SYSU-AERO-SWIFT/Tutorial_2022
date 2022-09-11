#include"ros/ros.h"
#include"pack2/test.h"
using namespace ros;

bool callback(pack2::test::Request& req, pack2::test::Response& res){
        if(req.ran<0.5)return true;
        else return false;
}


int main(int argc,char** argv){
   init(argc,argv,"server");

   NodeHandle n;

   ServiceServer server=n.advertiseService("/link",callback);

   spin();
}


