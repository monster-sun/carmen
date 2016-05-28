#include "ros/ros.h"
//#include <brazen_msgs/brazenbot.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/String.h"
#include <math.h>
int available = 0;
sensor_msgs::JointState rosserial_joint_states;
//char *a[] = {"joint1","joint2","joint3","joint4","joint5","joint6"};

//uint16_t convert_angle(double x)
//{
//  uint16_t y;
//  if (x > 0.0) {
//    // add 0.5 to properly round instead of trunkcates
//    y = (uint16_t) ((x * 180.0 / M_PI + 90.0) + 0.5);
//  }
//  else {
//    y = (uint16_t) (abs(x * 180.0 / M_PI + 90.0) + 0.5);
//  }
//  return y;
//}


void cmd_joints_Callback(const sensor_msgs::JointState js)
{
  //rosserial_joint_states.name[0] = "joints"; 
  //rosserial_joint_states.position[0] = js.position[0];
  //rosserial_joint_states.position[1] = js.position[1];
  //rosserial_joint_states.position[2] = js.position[2];
  //rosserial_joint_states.position[3] = js.position[3];
  //rosserial_joint_states.position[4] = js.position[4];
  //rosserial_joint_states.position[5] = js.position[5];
  //rosserial_joint_states.velocity[0] = js.velocity[0];
  //rosserial_joint_states.velocity[1] = js.velocity[1];
  //rosserial_joint_states.velocity[2] = js.velocity[2];
  //rosserial_joint_states.velocity[3] = js.velocity[3];
  //rosserial_joint_states.velocity[4] = js.velocity[4];
  //rosserial_joint_states.velocity[5] = js.velocity[5];
  available = 1;
  //brazen_arm.cmd_status = 1;
  //brazen_arm.servo_enable = 0xFFF;
  //brazen_arm.servo1a_pos = convert_angle(js.position[0]);
  //brazen_arm.servo2a_pos = convert_angle(js.position[1]);
  //brazen_arm.servo3a_pos = convert_angle(js.position[2]);
  //brazen_arm.servo4a_pos = 0xFF; //convert_angle(js.position[3]);
  //brazen_arm.servo5a_pos = 0xFF; //convert_angle(js.position[4]);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "carmen_joints");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("move_group/fake_controller_joint_states", 1000, cmd_joints_Callback);
  ros::Publisher pub_cmds_ = n.advertise<sensor_msgs::JointState>("move_group/rosserial_joint_states", 50, false);
 
  ros::Rate loop_rate(20);

  int count = 0;
  while (ros::ok())
  {
    //rosserial_joint_states.name<sensor_msgs::JointState> = "joints";
    //rosserial_joint_states.position = pos;
    //rosserial_joint_states.velocity = vel;
    //rosserial_joint_states.effort = eff;
    if(available==1){
    pub_cmds_.publish(rosserial_joint_states);}
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}


