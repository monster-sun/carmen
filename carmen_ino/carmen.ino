/*
 * brazenbot robot controller for arm
 * 
 * Controls RC servo motors for Brazenbot arm.  Safety limits
 * hard coded to protect arm.
 * 
 *
 * W. Lehman
 *
 * This sketch 
 */

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <carmen_msgs/carmen.h>
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

int init_flag = 0;

Servo servo1a;
Servo servo2a;
Servo servo3a;
Servo servo4a;

void cmd_cb( const carmen_msgs::carmen& cmd_arm){
  int serv1;
  int serv2;
  int serv3;
  int serv4; 
  if(cmd_arm.cmd_status == 1) {
    serv1 = cmd_arm.servo1a_pos;
    serv2 = cmd_arm.servo2a_pos;
    serv3 = cmd_arm.servo3a_pos;
    serv4 = cmd_arm.servo4a_pos;
    
    if (serv1 < 37) serv1 = 37;
    if (serv1 > 130) serv1 = 130;
    if (serv2 < 69) serv2 = 69;
    if (serv2 > 144) serv2 = 144;
    if (serv3 < 73) serv3 = 73;
    if (serv3 > 156) serv3 = 156;
    
    servo1a.write(serv1 + 2); //set servo angle, should be from 0-180  
    servo2a.write(serv2 - 26); //set servo angle, should be from 0-180  
    servo3a.write(180 - serv3 - 19); //set servo angle, should be from 0-180  
    servo4a.write(cmd_arm.servo4a_pos); //set servo angle, should be from 0-180  

  }
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
  init_flag = 0;
}


ros::Subscriber<brazen_msgs::brazenbot> sub("move_group/cmd_joints", cmd_cb);
//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);
//char hello[13] = "hello world!";

void setup(){
  pinMode(13, OUTPUT);
  
  init_flag = 1;
  
  nh.initNode();
  nh.subscribe(sub);
  //nh.advertise(chatter);
  
  servo1a.attach(8); //attach it to pin 9
  servo2a.attach(9);
  servo3a.attach(10);
  servo4a.attach(11);
  
  servo1a.write(90); //set servo angle, should be from 0-180  
  servo2a.write(90); //set servo angle, should be from 0-180  
  servo3a.write(90); //set servo angle, should be from 0-180  
  servo4a.write(90); //set servo angle, should be from 0-180 
  
   digitalWrite(13, 1);  //toggle led  

}

void loop(){
  nh.spinOnce();
  delay(1);
}
