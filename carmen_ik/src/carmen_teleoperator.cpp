#include "ros/ros.h"
#include "carmen_ik/Motor.h"
#include "carmen_ik/WriteMotor.h"  
#include "carmen_ik/ReadMotor.h"
//#include "brazo_fer/brazo_fer.h"  
#include "geometry_msgs/Point.h"
#include "std_msgs/Int16.h"
#include "std_msgs/String.h"  
#include <signal.h>
#include <termios.h>
#include <stdio.h> 

#define KEYCODE_Xmas 0x43 
#define KEYCODE_Xmenos 0x44
#define KEYCODE_Ymas 0x41
#define KEYCODE_Ymenos 0x42
#define KEYCODE_Zmas 0x77
#define KEYCODE_Zmenos 0x73
//#define KEYCODE_Pabrir 0x61
//#define KEYCODE_Pcerrar 0x64
//#define KEYCODE_PinclinarMas 0x65
//#define KEYCODE_PinclinarMenos 0x71  

struct termios cooked, raw; 

carmen_ik::Motor step;

double retardo = 0.11;

//geometry_msgs::Point punto;
 
void quit(int sig)
{
  tcsetattr(0, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
} 

void callback(const ros::TimerEvent&)
{
 
  //ros::NodeHandle n;      
  
  //ros::Publisher move_pub_=n.advertise<brazo_fer::WriteServos>("move_arm", 1);           

  ros::Time anterior;
        
  char c;

  // get the console in raw mode                                                              
  tcgetattr(0, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(0, TCSANOW, &raw);

  puts(""); 
  puts("#####################################################");
  puts("                      ARM CONTROLS");
  puts("#####################################################");
  puts("");  
  puts("Up arrow:___________ Move up gripper");
  puts("Down arrow:_________ Move down gripper");
  puts("Left arrow:_________ Move left gripper"); 
  puts("Right arrow:________ Move right gripper");
  puts("W key:______________ Move forward gripper");
  puts("S key:______________ Move backward gripper");
  puts("A key:______________ Open gripper");
  puts("D key:______________ Close gripper");
  puts("Q key:______________ Tilt up gripper");
  puts("E key:______________ Tilt down gripper");                 
              

        
  while (ros::ok())
  {
                              
  // get the next event from the keyboard  
    if(read(0, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
      
    if (c == KEYCODE_Xmas)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {
              step.base += 1;
              anterior = ros::Time::now();
              }                       
    }
    if (c == KEYCODE_Xmenos)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {      
              step.base -= 1;
              anterior = ros::Time::now();
              }                               
    }
    if (c == KEYCODE_Ymas)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {      
              step.joint2 += 1;
              anterior = ros::Time::now();
              }                                           
    }
    if (c == KEYCODE_Ymenos)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {      
              step.joint2 -= 1;        
              anterior = ros::Time::now();
              }                                               
    }
    if (c == KEYCODE_Zmas)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {      
              step.joint1 += 1;           
              anterior = ros::Time::now();
              }                                       
    }
    if (c == KEYCODE_Zmenos)
    {
              if (ros::Time::now() > anterior + ros::Duration(::retardo))
              {      
              step.joint1 -= 1;  
              anterior = ros::Time::now();
              }                               
    }                                  
              
    if ((205 <= ::step.base && ::step.base <= 818) && (-127 <= ::step.joint1 && ::step.joint1 <= 127) && (-127 <= ::step.joint2 && ::step.joint2 <= 127))
    {
        move_pub_.publish(step);                      
    }
                                                       
  }       
}
 
  int main(int argc, char **argv)
  {
 
        ros::init(argc, argv, "carmen_teleoperator");   
 
        ros::NodeHandle n;     
        
        ros::Publisher move_pub_=n.advertise<brazo_fer::Motor>("move_arm", 1);   
        
        //ros::Publisher hand_pub_=n.advertise<brazo_fer::WriteServos>("hand_arm", 1);    
                         

        signal(SIGINT,quit); 
        
        ros::Timer timer = n.createTimer(ros::Duration(1), callback);  
           
 
        ros::spin();  
 
        return 0;
  }