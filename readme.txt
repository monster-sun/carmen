carmen 6 DOF robotic arm for MBZIRC competition

# /carmen :
package containing carmen's URDF, created from converting Solidworks STL file

# /carmen_moveit_config :
package created from moveit_setup_assistant
- carmen_node.cpp : subscribe to <sensor_msgs::JointState> /move_group/fake_controller_joint_states and publish to <sensor_msgs::JointState> rosserial_joint_states
- move_group_random.cpp : randomly assign coordinate
- move_group_coordinate.cpp : move to a predefined coordinate in space
- move_group_coordinate2.cpp : subscribe to topic /point and then move to that coordinate in space by sending command "rostopic pub point geometry_msgs/Point '{x: -0.687822, y: 0.316510, z: 0.475076}' --once"

# /carmen_msgs :
package containing carmen_msgs for talking to arduino through rosserial

# /carmen_step :
contains arduino code for subscribing to <sensor_msgs::JointState>, convert the radian degree to steps and publishing them as /joint_steps

running rosserial connection :
rosrun rosserial_python serial_node.py /dev/ttyUSB0

# /wlehman :
folder containing reference codes from William Lehman

# Alternative to publishing topic for testing purpose :
rostopic pub /move_group/fake_controller_joint_states sensor_msgs/JointState '{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ""}, name: ["art1"], position: [150.0], velocity: [0.0], effort: [0.0]}' --once

replace name with: ["joint1,joint2,joint3,joint4,joint5,joint6"]
position: [1.2479490205621717, -0.6382032520635745, 0.25038124775567, -0.07965276236259244, -1.5680344280265524, 1.823960169093795]

# Update :
Using the above code and running Arduino Ros Serial Blink, the LED will blink. However when we publish 6 joints, it fail to blink. Maximum we could publish for the ros serial to blink is 3 joints
However, when I publish 1 joint with 6 float position with many decimal places, the blink works!
Problem is with the JointState.name! Try brazenbot_joints, I think you have to convert the JointState.name into char like specified here:
http://answers.ros.org/question/185245/sensor_msgsjointstate-on-arduino/

http://answers.ros.org/question/11887/significance-of-rosspinonce/?answer=17582#post-id-17582
