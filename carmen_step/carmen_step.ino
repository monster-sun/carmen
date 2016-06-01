/*
 * Arduino program to receive topic /move_group/fake_controller_joint_states
 * Radian angles will then be converted into steps before sending to 6 different stepper motors
 * 
 * 
 * Nicholas Adrian
 *
 * Reference: William Lehman
 *
 * PUL+ to pin 1-
 * PUL- to gnd
 * DIR+ to pin 11
 * DIR- to gnd
 * ENBL+ to pin 12
 * ENBL- to gnd
 */

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>

#define PUL 10
#define DIR 11
#define ENBL 12
#define POT A1

ros::NodeHandle  nh;
std_msgs::String str_msg;

int STEPS;
int joint_status = 0;
int stepper[6];
int joint_step[6];

uint16_t convert_angle(double x)
{
  uint16_t y;
  if (x > 0.0)
  {
    y = (uint16_t)((x* 180.0 / M_PI + 90.0) + 0.5); 
    y = (y/360)*STEPS;
  }
  else
  {
    y = (uint16_t) (abs(x * 180.0 / M_PI + 90.0) + 0.5);
    y = (y/360)*STEPS;
  }
  
}

void cmd_cb( const sensor_msgs::JointState& cmd_arm)
{
  digitalWrite(13, HIGH-digitalRead(13));  
  
  stepper[0] = cmd_arm.position[0];
  stepper[1] = cmd_arm.position[1];
  stepper[2] = cmd_arm.position[2];
  stepper[3] = cmd_arm.position[3];
  stepper[4] = cmd_arm.position[4];
  stepper[5] = cmd_arm.position[5];

  joint_step[0] = convert_angle(stepper[0]);
  joint_step[1] = convert_angle(stepper[1]);
  joint_step[2] = convert_angle(stepper[2]);
  joint_step[3] = convert_angle(stepper[3]);
  joint_step[4] = convert_angle(stepper[4]);
  joint_step[5] = convert_angle(stepper[5]);

  joint_status = 1;
}

ros::Subscriber<sensor_msgs::JointState> sub("/move_group/fake_controller_joint_states", cmd_cb);
ros::Publisher steps("joint_steps",&str_msg);

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(ENBL,OUTPUT);
  pinMode(POT, INPUT);
  pinMode(2, INPUT);

  digitalWrite(PUL,LOW);
  digitalWrite(DIR,LOW);
  digitalWrite(ENBL,LOW);
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(steps); 

}

void loop()
{
  char buf[50] = {};
  //str_msg.data = "hello world";
  str_msg.data = itoa(joint_step[3],buf,10);
  
  nh.spinOnce();
  delay(1);

  if(joint_status == 1)
  {
    steps.publish(&str_msg);
    
    if (digitalRead(2)== HIGH)
    {
    digitalWrite(DIR, LOW);
    }
    if (digitalRead(2)== LOW)
    {
    digitalWrite(DIR, HIGH);
    }

    digitalWrite(PUL, HIGH);
    delay(2000);
    digitalWrite(PUL, LOW);
    delay(2000);
    
     
  }
 }

  
