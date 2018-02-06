extern "C" {
#include <roboticscape.h>
}

extern "C" {
#include <rc_usefulincludes.h>
}

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include<sstream>

using namespace std;

void listenCallback(const std_msgs::String::ConstPtr& msg) {
 std::string newMsg;

 ROS_INFO("I hear you: [%s]", msg->data.c_str());

 newMsg = msg->data.c_str();
 rc_initialize();
 rc_enable_motors();

 if("hello" == newMsg) {
   rc_set_led(RED, ON);
   ROS_INFO("Welcome to the world");
 }

 if("forward" == newMsg) {
   //rc_set_motor_free_spin(1);
   //rc_set_motor_free_spin(2);
   rc_set_motor(1, 0.5);
   rc_set_motor(2, 0.5);
   ROS_INFO("Going forward");
 }

 if("stop" == newMsg) {
   rc_set_motor_brake(1);
   rc_set_motor_brake(2);
   ROS_INFO("Brake/stopped");
 }

 if("shutdown" == newMsg) {
   rc_cleanup();
   ros::shutdown();
   ROS_INFO("Shutting down ROS Node");
 }

}

int main(int argc, char **argv) {

 ros::init(argc, argv, "listener");
 ROS_INFO("Node initiated");
 ros::NodeHandle listen;

 if(rc_initialize() <0){
   ROS_INFO("Error: failed to initialize cape.");
   return -1;
 }

 ros::Subscriber sub = listen.subscribe("command", 1000, listenCallback);
 ROS_INFO("Node Started");

 ros::spin();

 return 0;
}
