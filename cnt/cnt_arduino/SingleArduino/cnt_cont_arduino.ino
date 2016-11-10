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

int16_t joint_step;
uint16_t rpm;
int joint_status = 0;

ros::NodeHandle nh;
//std_msgs::String str_msg;

void cmd_cb(const cnt::ArmJointState& arm_steps){
  //digitalWrite(13, HIGH-digitalRead(13));
  joint_status = 1;

  joint_step = arm_steps.position[0];
  rpm = arm_steps.rpm[0];
}

ros::Subscriber<cnt::ArmJointState> sub("/cnt/output_steps", &cmd_cb);
//ros::Publisher steps("joint_steps_feedback",&str_msg);

const int stepsPerRevolution = 400;
Stepper stepper1(stepsPerRevolution,9,11);

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
    digitalWrite(13, HIGH);
    if (joint_step[0]!=0)
    {
      //move joint1
      //stepper1.setSpeed(rpm);
      //stepper1.step(joint_step);
      //Serial.println("joint_step[0] :");
      //Serial.print(joint_step[0]);
      nh.loginfo("joint_step and rpm received");
    }
    digitalWrite(13,LOW);
    joint_status = 0;
  }
}
