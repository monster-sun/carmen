/*
 * Arduino program to receive topic /move_group/fake_controller_joint_states
 * Radian angles will then be converted into steps before sending to 6 different stepper motors
 * 
 * 
 * Nicholas Adrian
 *
 * Reference: William Lehman
 *
 * Things to do:
 * 1. Assign pins for DIRx and PULx
 * 2. itoa is giving a delay (sending previous command instead of the recent command)
 */

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <math.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
#include <stdlib.h>

#define DIR0 11
#define PUL0 10
#define DIR1 9
#define PUL1 9
#define DIR2 9
#define PUL2 9
#define DIR3 9
#define PUL3 9
#define DIR4 9
#define PUL4 9 
#define DIR5 9
#define PUL5 9

#define ENBL 12
#define POT A1

ros::NodeHandle nh;
std_msgs::String str_msg;

int STEPS = 400;
int joint_status = 0;
double stepper[6];
int joint_step[6];
int previous_step[6];

int convert_angle(double x)
{
  float y;
  y=((x / M_PI)*STEPS)+0.5;
  return y*49;
}

int j;

void cmd_cb( const sensor_msgs::JointState& cmd_arm)
{
  //digitalWrite(13, HIGH-digitalRead(13));
  
  stepper[0] = cmd_arm.position[0];
  stepper[1] = cmd_arm.position[1];
  stepper[2] = cmd_arm.position[2];
  stepper[3] = cmd_arm.position[3];
  stepper[4] = cmd_arm.position[4];
  stepper[5] = cmd_arm.position[5];

  joint_step[0] = convert_angle(stepper[0])-previous_step[0];
  joint_step[1] = convert_angle(stepper[1])-previous_step[1];
  joint_step[2] = convert_angle(stepper[2])-previous_step[2];
  joint_step[3] = convert_angle(stepper[3])-previous_step[3];
  joint_step[4] = convert_angle(stepper[4])-previous_step[4];
  joint_step[5] = convert_angle(stepper[5])-previous_step[5];

  previous_step[0] = joint_step[0];
  previous_step[1] = joint_step[1];
  previous_step[2] = joint_step[2];
  previous_step[3] = joint_step[3];
  previous_step[4] = joint_step[4];
  previous_step[5] = joint_step[5];
  
  joint_status = 1;
}

ros::Subscriber<sensor_msgs::JointState> sub("/move_group/fake_controller_joint_states", cmd_cb);
//Publisher
ros::Publisher steps("joint_steps",&str_msg);
int t=0;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(DIR0, OUTPUT);
  pinMode(PUL0, OUTPUT);
//  pinMode(DIR1, OUTPUT);
//  pinMode(PUL1, OUTPUT);
//  pinMode(DIR2, OUTPUT);
//  pinMode(PUL2, OUTPUT);
//  pinMode(DIR3, OUTPUT);
//  pinMode(PUL3, OUTPUT);
//  pinMode(DIR4, OUTPUT);
//  pinMode(PUL4, OUTPUT);
//  pinMode(DIR5, OUTPUT);
//  pinMode(PUL5, OUTPUT);
  pinMode(ENBL,OUTPUT);
  pinMode(POT, INPUT);
  pinMode(2, INPUT);

  digitalWrite(PUL0,LOW);
  digitalWrite(DIR0,LOW);
//  digitalWrite(PUL1,LOW);
//  digitalWrite(DIR1,LOW);
//  digitalWrite(PUL2,LOW);
//  digitalWrite(DIR2,LOW);
//  digitalWrite(PUL3,LOW);
//  digitalWrite(DIR3,LOW);
//  digitalWrite(PUL4,LOW);
//  digitalWrite(DIR4,LOW);
//  digitalWrite(PUL5,LOW);
//  digitalWrite(DIR5,LOW);
  digitalWrite(ENBL,LOW);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(steps); 

}

void loop()
{
  char buf[50] = {};
  //str_msg.data = "hello world";
  str_msg.data = itoa(joint_step[1],buf,10);

  nh.spinOnce();
  delay(1);

  if(joint_status == 1)
  {
    steps.publish(&str_msg);

    if (joint_step[0] >= 0)
      {
        for(t=0;t<=joint_step[0];t++)
        {
          digitalWrite(DIR0, HIGH);
          digitalWrite(PUL0, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL0, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[0] < 0)
      {
        for(t=0;t>=joint_step[0];t--)
        {
          digitalWrite(DIR0, LOW);
          digitalWrite(PUL0, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL0, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[1] > 0)
      {
        for(t=0;t<=joint_step[1];t++)
        {
          digitalWrite(DIR1, HIGH);
          digitalWrite(PUL1, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL1, LOW);
          delayMicroseconds(300)
          ;
        }
        joint_status = 0;
      }
    if (joint_step[1] < 0)
      {
        for(t=0;t>=joint_step[1];t--)
        {
          digitalWrite(DIR1, LOW);
          digitalWrite(PUL1, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL1, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;;
      }
    if (joint_step[2] > 0)
      {
        for(t=0;t<=joint_step[2];t++)
        {
          digitalWrite(DIR2, HIGH);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL2, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[2] < 0)
      {
        for(t=0;t>=joint_step[2];t--)
        {
          digitalWrite(DIR2, LOW);
          digitalWrite(PUL2, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL2, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[3] > 0)
      {
        for(t=0;t<=joint_step[3];t++)
        {
          digitalWrite(DIR3, HIGH);
          digitalWrite(PUL3, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL3, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[3] < 0)
      {
        for(t=0;t>=joint_step[3];t--)
        {
          digitalWrite(DIR3, LOW);
          digitalWrite(PUL3, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL3, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[4] > 0)
      {
        for(t=0;t<=joint_step[4];t++)
        {
          digitalWrite(DIR4, HIGH);
          digitalWrite(PUL4, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL4, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[4] < 0)
      {
        for(t=0;t>=joint_step[4];t--)
        {
          digitalWrite(DIR4, LOW);
          digitalWrite(PUL4, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL4, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[5] > 0)
      {
        for(t=0;t<=joint_step[5];t++)
        {
          digitalWrite(DIR5, HIGH);
          digitalWrite(PUL5, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL5, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
    if (joint_step[5] < 0)
      {
        for(t=0;t>=joint_step[5];t--)
        {
          digitalWrite(DIR5, LOW);
          digitalWrite(PUL5, HIGH);
          delayMicroseconds(300);
          digitalWrite(PUL5, LOW);
          delayMicroseconds(300);
        }
        joint_status = 0;
      }
     
  }
 }

  
