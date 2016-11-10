I2C/
--Master/
----WireMaster_stepperlib/ #Master I2C connection + stepper.h for stepper movement
----WireMaster_loop/ #Master I2C connection + for_loop for stepper movement
--Slave/
----WireSlave_stepperlib/ #Slave I2C connection + stepper.h for stepper movement
----WireSlave_loop/ #Slave I2C connection + for_loop for stepper movement

SingleArduino/ #Initial attempt to control 6 stepper motors with one arduino
--cnt_cont_arduino.ino #continuous movement
--cnt_disc_arduino.ino #discrete movement (step-by-step)

