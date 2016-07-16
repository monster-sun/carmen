#include <ros.h>
#include <carmen_ik/Motor.h>
#include <carmen_ik/WriteMotor.h>
#include <carmen_ik/ReadMotor.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>

double joint_step[6];
int joint_status = 0;
int STEPS = 400;
#define gear_ratio 49

ros::NodeHandle nh;
std_msgs::String str_msg;

int convert_gear(double x) // Apply gear ratio
{
  float y;
  y=((x / 360)*STEPS)+0.5;
  return y*gear_ratio;
}

void move(const carmen_ik::Motor& motor){
  joint_status = 1;

  joint_step[0] = convert_gear(motor.joint1);
  joint_step[1] = convert_gear(motor.joint2);
  joint_step[2] = convert_gear(motor.joint3);
  joint_step[3] = convert_gear(motor.joint4);
  joint_step[4] = convert_gear(motor.joint5);
}

ros::Subscriber<carmen_ik::Motor> move_sub("move_arm",&move);
ros::Publisher steps("joint_steps",&str_msg);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(move_sub);
}

void loop() {
  char buf[50] = {};
  str_msg.data = itoa(joint_step[1],buf,10);
  
  nh.spinOnce();
  delay(1);

  if (joint_status == 1)
  {
    digitalWrite(13, HIGH-digitalRead(13));
    if (joint_step[0] >= 0)
    {
      //move joint1
    }

    joint_status = 0;
  }
}
