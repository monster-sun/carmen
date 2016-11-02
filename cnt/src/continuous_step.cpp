#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "cnt/ArmJointState.h"
#include "math.h"

cnt::ArmJointState arm_steps;
static bool initializedTime;
int STEPS = 400;
uint8_t TimePerMotion;
uint8_t gear_ratio = 49;
uint16_t MotorStepsPerRev = 400;
uint8_t setTime_buffer = 2;
uint16_t maxRPM = 600;
int joint_status = 0;
int16_t previous_step[6] = {0,0,0,0,0,0};

uint8_t setTime()
{
  float minTime;
  minTime = (60/maxRPM)*gear_ratio;
  return minTime+setTime_buffer;
}

uint16_t setRPM(uint16_t gearbox_steps)
{
  ROS_INFO_STREAM("In setRPM function");
  float rpm;
  rpm = (60*gearbox_steps)/(TimePerMotion*MotorStepsPerRev*gear_ratio);
  ROS_INFO_STREAM("Done calculating rpm");
  return rpm;
}

int16_t convert_angle(double x)
{
  ROS_INFO_STREAM("In convert_angle function");
  float y;
  ROS_INFO_STREAM("a");
  y=((x / M_PI)*STEPS)+0.5;
  ROS_INFO_STREAM("Done calculating steps");
  return y*gear_ratio;
}

void cmd_cb(const sensor_msgs::JointState& cmd_arm)
{
  //ros::NodeHandle nh;
  //ros::Subscriber sub = nh.subscribe("/cnt/input_angles",1000,cmd_cb);
  //ros::Publisher pub = nh.advertise<cnt::ArmJointState>("/cnt/output_steps",50);
  ROS_INFO_STREAM("Received /cnt/input_angles");
  
  arm_steps.position[0] = convert_angle(cmd_arm.position[0])-previous_step[0];
  arm_steps.position[1] = convert_angle(cmd_arm.position[1])-previous_step[1];
  arm_steps.position[2] = convert_angle(cmd_arm.position[2])-previous_step[2];
  arm_steps.position[3] = convert_angle(cmd_arm.position[3])-previous_step[3];
  arm_steps.position[4] = convert_angle(cmd_arm.position[4])-previous_step[4];
  arm_steps.position[5] = convert_angle(cmd_arm.position[5])-previous_step[5];
  ROS_INFO_STREAM("Converted angles to arm_steps.position[]");

  arm_steps.rpm[0] = setRPM(arm_steps.position[0]);
  arm_steps.rpm[1] = setRPM(arm_steps.position[1]);
  arm_steps.rpm[2] = setRPM(arm_steps.position[2]);
  arm_steps.rpm[3] = setRPM(arm_steps.position[3]);
  arm_steps.rpm[4] = setRPM(arm_steps.position[4]);
  arm_steps.rpm[5] = setRPM(arm_steps.position[5]);

  previous_step[0] = arm_steps.position[0];
  previous_step[1] = arm_steps.position[1];
  previous_step[2] = arm_steps.position[2];
  previous_step[3] = arm_steps.position[3];
  previous_step[4] = arm_steps.position[4];
  previous_step[5] = arm_steps.position[5];

  ROS_INFO_STREAM("Done conversion to /cnt/output_steps");
  joint_status = 1;
}

int main(int argc, char **argv)
{
  if(!initializedTime){
    initializedTime = true;
    TimePerMotion = setTime();
  }
  ros::init(argc, argv, "cnt_continuous_step");
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
