#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

extern "C"
{
 #include <roboticscape.h>
}

extern "C"
{
#include <rc_usefulincludes.h>
}

int main(int argc, char **argv) {
 ros::init(argc, argv, "talker");
 ros::NodeHandle n;

 ros::Publisher chat_pub = n.advertise<std_msgs::String>("chatter", 1000);
 ros::Rate loop_rate(10);

 int count = 0;

 if(rc_initialize() < 0)
   {
      ROS_INFO("Error: failed to initialize cape."); 
   }

 while(ros::ok()) {

 std_msgs::String msg;
 std::stringstream ss;
 ss << "helloooo... again" << count;
 msg.data = ss.str();
 ROS_INFO("%s", msg.data.c_str());
 chat_pub.publish(msg);

// rc_initialize();
// rc_set_led(GREEN, ON);

 ros::spinOnce();

 loop_rate.sleep();
 ++count;

 }
 return 0;

}
