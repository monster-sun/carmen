rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=57600

rostopic pub /cnt/input_angles sensor_msgs/JointState '{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ""}, name: ["joint1,joint2,joint3,joint4,joint5,joint6"], position: [1.2479490205621717, -0.6382032520635745, 0.25038124775567, -0.07965276236259244, -1.5680344280265524, 1.823960169093795], velocity: [0.0], effort: [0.0]}' --once

References for Arduino I2C:
[1]http://dsscircuits.com/articles/arduino-i2c-slave-guide
[2]https://thewanderingengineer.com/2015/05/06/sending-16-bit-and-32-bit-numbers-with-arduino-i2c/
