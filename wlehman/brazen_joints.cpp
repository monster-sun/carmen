#include "ros/ros.h"
#include <brazen_msgs/brazenbot.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/String.h"
#include <math.h>


uint16_t convert_angle(double x)
{
  uint16_t y;
  if (x > 0.0) {
    // add 0.5 to properly round instead of trunkcates
    y = (uint16_t) ((x * 180.0 / M_PI + 90.0) + 0.5);
  }
  else {
    y = (uint16_t) (abs(x * 180.0 / M_PI + 90.0) + 0.5);
  }
  return y;
}

brazen_msgs::brazenbot brazen_arm;

void cmd_joints_Callback(const sensor_msgs::JointState js)
{


  brazen_arm.cmd_status = 1;
  brazen_arm.servo_enable = 0xFFF;
  brazen_arm.servo1a_pos = convert_angle(js.position[0]);
  brazen_arm.servo2a_pos = convert_angle(js.position[1]);
  brazen_arm.servo3a_pos = convert_angle(js.position[2]);
  brazen_arm.servo4a_pos = 0xFF; //convert_angle(js.position[3]);
  brazen_arm.servo5a_pos = 0xFF; //convert_angle(js.position[4]);
  brazen_arm.servo6a_pos = 0xFF; //convert_angle(js.position[5]);
  brazen_arm.servo1b_pos = 0xFF; //convert_angle(js.position[6]);
  brazen_arm.servo2b_pos = 0xFF; //convert_angle(js.position[7]);
  brazen_arm.servo3b_pos = 0xFF; //convert_angle(js.position[8]);
  brazen_arm.servo4b_pos = 0xFF; //convert_angle(js.position[9]);
  brazen_arm.servo5b_pos = 0xFF; //convert_angle(js.position[10]);
  brazen_arm.servo6b_pos = 0xFF; //convert_angle(js.position[11]);

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "brazen_joints");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joint_states", 100, cmd_joints_Callback);
  ros::Publisher pub_cmds_ = n.advertise<brazen_msgs::brazenbot>("move_group/cmd_joints", 50, false);
 
  ros::Rate loop_rate(20);

  int count = 0;
  while (ros::ok())
  {
    pub_cmds_.publish(brazen_arm);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}


