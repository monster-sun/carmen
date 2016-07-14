#include <ros.h>
#include <carmen_ik/Motor.h>
#include <carmen_ik/WriteMotor.h>
#include <carmen_ik/ReadMotor.h>
#include <std_msgs/Bool.h>
#include <math.h>

double joint_step[6];
int joint_status = 0;
#define gear_ratio 49

ros::NodeHandle nh;

int convert_gear(double x) // Apply gear ratio
{
  float y;
  y=((x+0.5)*gear_ratio);
  return y;
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
void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(move_sub);
}

void loop() {
  // put your main code here, to run repeatedly:
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
