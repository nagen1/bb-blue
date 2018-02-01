#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

using namespace std;

void listenCallback(const std_msgs::ConstPtr& msg) {
 std::string newMsg;
 
 ROS_INFO("I hear you: [%s]", msg->data.c_str());
 
 newMsg = msg->data.c_str();
 
 if("forward" == newMsg) {
   ROS_INFO("Welcome to the world");
 }
 
}

int main(int argc, char **argv) {
 
 ros::init(argc, argv, "listener");
 ros::NodeHandle listen;
 
 ROS_INFO("Node initiated");
 ros::Subscriber sub = listen.subscribe("command", 1000, listenCallback);
 ROS_INFO("Node Started");
 
 ros::spin();
 
 return 0;
}
