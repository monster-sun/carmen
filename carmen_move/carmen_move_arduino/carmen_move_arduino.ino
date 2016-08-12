#include <Arduino.h>
#include <ros.h>
#include <carmen_move/ArmJointState.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>

int joint_step[6];
int joint_status = 0;

ros::NodeHandle nh;
std_msgs::String str_msg;

void cmd_cb(const carmen_move::ArmJointState& arm_steps){
  //digitalWrite(13, HIGH-digitalRead(13));
  joint_status = 1;

  joint_step[0] = arm_steps.position[0];
  joint_step[1] = arm_steps.position[1];
  joint_step[2] = arm_steps.position[2];
  joint_step[3] = arm_steps.position[3];
  joint_step[4] = arm_steps.position[4];
  joint_step[5] = arm_steps.position[5];
}

ros::Subscriber<carmen_move::ArmJointState> sub("joint_steps",&cmd_cb);
//ros::Publisher steps("joint_steps_feedback",&str_msg);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
  pinMode(13,OUTPUT);
}

void loop() {
  //char buf[50] = {};
  //str_msg.data = itoa(joint_step[1],buf,10);
  
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
