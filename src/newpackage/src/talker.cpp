//#include <ros/ros.h>
//#include <std_msgs/String.h>
//#include <sstream>

extern "C"
{
 #include <roboticscape.h>
}

extern "C"
{
#include <rc_usefulincludes.h>
}

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

int main(int argc, char **argv) {
 ros::init(argc, argv, "talker");
 ros::NodeHandle n;

 ros::Publisher chat_pub = n.advertise<std_msgs::String>("chatter", 1000);
 ros::Rate loop_rate(50);

 int count = 0;

 if(rc_initialize() < 0)
   {
      ROS_INFO("Error: failed to initialize cape.");
   }

 rc_set_state(RUNNING);
// rc_set_led(RED, ON);
 rc_enable_motors();
 rc_set_motor_free_spin(1);
 rc_set_motor_free_spin(2);
 ROS_INFO("Motors are  ready now");

 while(ros::ok()) {

 std_msgs::String msg;
 std::stringstream ss;
 ss << "helloooo... again" << count;
 msg.data = ss.str();
 ROS_INFO("%s", msg.data.c_str());
 chat_pub.publish(msg);

// rc_set_state(RUNNING);
// rc_set_led(GREEN, ON);
 rc_set_led(RED, ON);

// rc_set_motor(1, 0.5);
// rc_set_motor(2, 0.5);

 ros::spinOnce();
 loop_rate.sleep();
// rc_cleanup();
 ++count;

 }
 rc_disable_motors();
 rc_cleanup();
 rc_set_state(EXITING);
 system("stty cooked");
 ROS_INFO("stty-cooked.....");

 return 0;

}
