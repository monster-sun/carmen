#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <ros.h>
#include <cnt/ArmJointState.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>
#include <std_msgs/Int16.h>
#include <Stepper.h>

int16_t joint_step[6];
int joint_status = 0;

ros::NodeHandle nh;
//std_msgs::String str_msg;

void cmd_cb(const cnt::ArmJointState& arm_steps){
  //digitalWrite(13, HIGH-digitalRead(13));
  joint_status = 1;

  joint_step[0] = arm_steps.position[0];
  joint_step[1] = arm_steps.position[1];
  joint_step[2] = arm_steps.position[2];
  joint_step[3] = arm_steps.position[3];
  joint_step[4] = arm_steps.position[4];
  joint_step[5] = arm_steps.position[5];
}

ros::Subscriber<cnt::ArmJointState> sub("/cnt/output_steps", &cmd_cb);
//ros::Publisher steps("joint_steps_feedback",&str_msg);

const int stepsPerRevolution = 400;
Stepper stepper1(stepsPerRevolution,9,11);
//Stepper stepper2(stepsPerRevolution,9,11);
//Stepper stepper3(stepsPerRevolution,9,11);
//Stepper stepper4(stepsPerRevolution,9,11);
//Stepper stepper5(stepsPerRevolution,9,11);
//Stepper stepper6(stepsPerRevolution,9,11);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
  pinMode(13,OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  //char buf[50] = {};
  //str_msg.data = itoa(joint_step[1],buf,10);
  
  nh.spinOnce();
  delay(1);

  if (joint_status == 1)
  {
    digitalWrite(13, HIGH-digitalRead(13));
    if (joint_step[0]!=0)
    {
      //move joint1
      //stepper1.step(joint_step);
      //Serial.println("joint_step[0] :");
      //Serial.print(joint_step[0]);
      nh.loginfo("joint_step[0] received");
    }

    if (joint_step[1]!=0)
    {
      //move joint2
      //stepper2.step(joint_step);
      //Serial.println("joint_step[1] :");
      //Serial.print(joint_step[1]);
      nh.loginfo("joint_step[1] received");
    }

    if (joint_step[2]!=0)
    {
      //move joint3
      //stepper3.step(joint_step);
      //Serial.println("joint_step[2] :");
      //Serial.print(joint_step[2]);
      nh.loginfo("joint_step[2] received");
    }

    if (joint_step[3]!=0)
    {
      //move joint4
      //stepper4.step(joint_step);
      //Serial.println("joint_step[3] :");
      //Serial.print(joint_step[3]);
      nh.loginfo("joint_step[3] received");
    }

    if (joint_step[4]!=0)
    {
      //move joint5
      //stepper5.step(joint_step);
      //Serial.println("joint_step[4] :");
      //Serial.print(joint_step[4]);
      nh.loginfo("joint_step[4] received");
    }

    if (joint_step[5]!=0)
    {
      //move joint6
      //stepper6.step(joint_step);
      //Serial.println("joint_step[5] :");
      //Serial.print(joint_step[5]);
      nh.loginfo("joint_step[5] received");
    }

    joint_status = 0;
  }
}
