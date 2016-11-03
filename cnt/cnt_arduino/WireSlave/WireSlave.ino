// Wire Slave Receiver

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

int16_t step1,step2,step3,step4,step5,step6;
int16_t rpm1,rpm2,rpm3,rpm4,rpm5,rpm6;
byte s11,s12,s21,s22,s31,s32,s41,s42,s51,s52,s61,s62;
byte r11,r12,r21,r22,r31,r32,r41,r42,r51,r52,r61,r62;

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  s11=Wire.read(); s12=Wire.read(); s21=Wire.read(); s22=Wire.read(); s31=Wire.read(); s32=Wire.read(); s41=Wire.read(); s42=Wire.read(); s51=Wire.read(); s52=Wire.read(); s61=Wire.read(); s62=Wire.read();
  r11=Wire.read(); r12=Wire.read(); r21=Wire.read(); r22=Wire.read(); r31=Wire.read(); r32=Wire.read(); r41=Wire.read(); r42=Wire.read(); r51=Wire.read(); r52=Wire.read(); r61=Wire.read(); r62=Wire.read();
  step1=s11; step1=(step1<<8)|s12; step2=s21; step2=(step2<<8)|s22; step3=s31; step3=(step3<<8)|s32;
  step4=s41; step4=(step4<<8)|s42; step5=s51; step5=(step5<<8)|s52; step6=s61; step6=(step6<<8)|s62;
  rpm1=r11; rpm1=(rpm1<<8)|r12; rpm2=r21; rpm2=(rpm2<<8)|r22; rpm3=r31; rpm3=(rpm3<<8)|r32;
  rpm4=r41; rpm4=(rpm4<<8)|r42; rpm5=r51; rpm5=(rpm5<<8)|r52; rpm6=r61; rpm6=(rpm6<<8)|r62;

  Serial.println("Reading");
  Serial.print("STEPS:   ");
  Serial.print(step1); Serial.print(" "); Serial.print(step2); Serial.print(" "); Serial.print(step3); Serial.print(" "); Serial.print(step4); Serial.print(" "); Serial.print(step5); Serial.print(" "); Serial.println(step6);
  Serial.print("RPM:     ");
  Serial.print(rpm1); Serial.print(" "); Serial.print(rpm2); Serial.print(" "); Serial.print(rpm3); Serial.print(" "); Serial.print(rpm4); Serial.print(" "); Serial.print(rpm5); Serial.print(" "); Serial.println(rpm6);
  Serial.println(" ");
}
