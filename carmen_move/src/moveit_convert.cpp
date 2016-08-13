#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "carmen_move/ArmJointState.h"
#include "math.h"

carmen_move::ArmJointState arm_steps;
int STEPS = 400;
#define gear_ratio 49
int joint_status = 0;
double angle[6];
int joint_step[6];
int previous_step[6] = {0,0,0,0,0,0};

int convert_angle(double x)
{
  float y;
  y=((x / M_PI)*STEPS)+0.5;
  return y*gear_ratio;
}

void cmd_cb(const sensor_msgs::JointState& cmd_arm)
{
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/move_group/fake_controller_joint_states",1000,cmd_cb);
  ros::Publisher pub = nh.advertise<carmen_move::ArmJointState>("joint_steps",50);
  ROS_INFO_STREAM("Received /move_group/fake_controller_joint_states");
  
  arm_steps.position1 = convert_angle(cmd_arm.position[0])-previous_step[0];
  arm_steps.position2 = convert_angle(cmd_arm.position[1])-previous_step[1];
  arm_steps.position3 = convert_angle(cmd_arm.position[2])-previous_step[2];
  arm_steps.position4 = convert_angle(cmd_arm.position[3])-previous_step[3];
  arm_steps.position5 = convert_angle(cmd_arm.position[4])-previous_step[4];
  arm_steps.position6 = convert_angle(cmd_arm.position[5])-previous_step[5];

  previous_step[0] = arm_steps.position1;
  previous_step[1] = arm_steps.position2;
  previous_step[2] = arm_steps.position3;
  previous_step[3] = arm_steps.position4;
  previous_step[4] = arm_steps.position5;
  previous_step[5] = arm_steps.position6;

  ROS_INFO_STREAM("Done conversion to /joint_steps");
  joint_status = 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "carmen_move");
  ros::NodeHandle nh;
  ROS_INFO_STREAM("In main function");
  ros::Subscriber sub = nh.subscribe("/move_group/fake_controller_joint_states",1000,cmd_cb);
  ros::Publisher pub = nh.advertise<carmen_move::ArmJointState>("joint_steps",50);
  
  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    if(joint_status==1)
    {
      joint_status = 0;
      pub.publish(arm_steps);
      ROS_INFO_STREAM("Published to /joint_steps");
    }
    ros::spinOnce();
    loop_rate.sleep();
    
  }

  
  //ros::spin();
  return 0;
}
