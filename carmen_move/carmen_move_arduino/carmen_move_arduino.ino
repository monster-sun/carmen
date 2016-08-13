#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <ros.h>
#include <carmen_move/ArmJointState.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>
#include <std_msgs/UInt8.h>

int joint_step[6];
int joint_status = 0;

ros::NodeHandle nh;
//std_msgs::String str_msg;

void cmd_cb(const carmen_move::ArmJointState& arm_steps){
  //digitalWrite(13, HIGH-digitalRead(13));
  joint_status = 1;

  joint_step[0] = arm_steps.position1;
  joint_step[1] = arm_steps.position2;
  joint_step[2] = arm_steps.position3;
  joint_step[3] = arm_steps.position4;
  joint_step[4] = arm_steps.position5;
  joint_step[5] = arm_steps.position6;
}

ros::Subscriber<carmen_move::ArmJointState> sub("joint_steps", &cmd_cb);
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
