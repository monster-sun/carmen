#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "cnt/ArmJointState.h"
#include "math.h"

cnt::ArmJointState arm_steps;
int STEPS = 400;
#define gear_ratio 49
int joint_status = 0;
int16_t previous_step[6] = {0,0,0,0,0,0};

int16_t convert_angle(double x)
{
  float y;
  y=((x / M_PI)*STEPS)+0.5;
  return y*gear_ratio;
}

void cmd_cb(const sensor_msgs::JointState& cmd_arm)
{
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/cnt/input_angles",1000,cmd_cb);
  ros::Publisher pub = nh.advertise<cnt::ArmJointState>("/cnt/output_steps",50);
  ROS_INFO_STREAM("Received /cnt/input_angles");
  
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

  ROS_INFO_STREAM("Done conversion to /cnt/output_steps");
  joint_status = 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cnt_discrete_step");
  ros::NodeHandle nh;
  ROS_INFO_STREAM("In main function");
  ros::Subscriber sub = nh.subscribe("/cnt/input_angles",1000,cmd_cb);
  ros::Publisher pub = nh.advertise<cnt::ArmJointState>("/cnt/output_steps",50);
  
  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    if(joint_status==1)
    {
      joint_status = 0;
      pub.publish(arm_steps);
      ROS_INFO_STREAM("Published to cnt/output_steps");
    }
    ros::spinOnce();
    loop_rate.sleep();
    
  }

  
  //ros::spin();
  return 0;
}
