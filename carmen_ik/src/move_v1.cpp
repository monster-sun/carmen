#include "ros/ros.h"
#include "carmen_ik/Motor.h"
#include "carmen_ik/WriteMotor.h"
#include "carmen_ik/ReadMotor.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Empty.h"
#include "math.h"

#define PI 3.14159265
#define L1 401.29
#define L2 397.854225
#define Lp 83
#define STEPS 400
#define base_adjust 150
#define joint1_adjust 60
#define joint2_adjust 30
#define joint3_adjust 30

carmen_ik::Motor initialize,step;

void init(const std_msgs::Empty& init)
{
    ::initialize.base = ((base_adjust)*STEPS)/360;
    ::initialize.joint1 = ((joint1_adjust)*STEPS)/360;
    ::initialize.joint2 = ((joint2_adjust)*STEPS)/360;
    ::initialize.joint3 = ((joint3_adjust)*STEPS)/360;
}

void ik(const geometry_msgs::Point& point)
{
    double x = point.x;
    double y = point.y;
    double z = point.z;
   
    y = y + z*tan(atan2(45,250)); //?

    int coordenadas_correctas = 1; //?

    double alfa, beta, beta_a, beta_p, beta_pp, gamma, delta, delta_a, delta_p, epsilon;
    double z_p;
    double L_a, L;

    epsilon = 0;
    alfa = (atan2(x,z)*180)/PI;

    z_p = sqrt(pow(z,2)+pow(x,2));

    L = sqrt(pow(z_p,2)+pow(y,2));

    L_a = sqrt(pow(y+(Lp*sin(epsilon)),2)+pow(z_p-(Lp*cos(epsilon)),2));
 
    beta_p = atan2(y+(Lp*sin(epsilon)),z_p-(Lp*cos(epsilon)));

    beta_pp = atan2(y,z_p);

    beta_a = acos((pow(L1,2)+pow(L_a,2)-pow(L2,2))/(2*L1*L_a));

    beta = ((beta_p+beta_a)*180)/PI;

    gamma = acos((pow(L1,2)+pow(L2,2)-pow(L_a,2))/(2*L1*L2));

    delta_a = PI-(beta_a+gamma);

    gamma = (gamma*180)/PI;

    delta_p = acos((pow(L_a,2)+pow(Lp,2)-pow(L,2))/(2*L_a*Lp));       

    if (beta_pp > beta_p) {
	    delta = ((2*PI-(delta_p-delta_a))*180)/PI;
    }
    else {
	    delta = ((delta_p+delta_a)*180)/PI;

	    if (isnan(delta)) {
		    delta = ((PI+delta_a)*180)/PI;
	    }
    }

    if (isnan(gamma)) // if no solution
    {
	    coordenadas_correctas = 0; 
    }

    ::step.base = ((alfa+base_adjust)*STEPS)/360;
    ::step.joint1 = ((beta+joint1_adjust)*STEPS)/360;
    ::step.joint2 = ((gamma-joint2_adjust)*STEPS)/360;
    ::step.joint3 = ((delta-joint3_adjust)*STEPS)/360;

    move_pub_.publish(step);

    //::vel.base = abs(::move.base - ::p.base)/5;
    //::vel.arti1 = abs(::move.arti1 - ::p.arti1)/5;
    //::vel.arti2 = abs(::move.arti2 - ::p.arti2)/5;
    //::vel.arti3 = abs(::move.arti3 - ::p.arti3)/5;
    //::vel.pinza = abs(::move.pinza - ::p.pinza);
    
    if (coordenadas_correctas == 1 && (205 <= ::step.base && ::step.base <= 818) && (-127 <= ::step.joint1 && ::step.joint1 <= 127) && (-127 <= ::step.joint2 && ::step.joint2 <= 127) && (-199 <= ::step.joint3 && ::step.joint3 <= 199)) {

	    carmen_ik::Motor move;

	    move.base = step.base;
	    move.joint1 = step.joint1;
	    move.joint2 = step.joint2;
	    move.joint3 = step.joint3;
	    
	    move_pub_.publish(move);
    }
    else {
	    std::cout<<"Error, invalid coordinates or unattainable point"<<std::endl;                               
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "carmen_control");
    ros::NodeHandle nh;
 
    ros::Subscriber init_sub = nh.subscribe("initialize",1,init);
    ros::Subscriber point_sub_= nh.subscribe("point",1,ik);
    ros::Publisher move_pub_ = nh.advertise<carmen_ik::Motor>("move_arm",1);

    ros::spin();
    return 0;
}
