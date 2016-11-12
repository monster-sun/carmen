// Wire Slave Receiver

#include <Wire.h>

#define PUL 10
#define DIR 11
#define SlaveID 2

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(PUL,LOW);
  digitalWrite(DIR,LOW);
  Wire.begin(SlaveID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

int16_t step1,step2,step3,step4,step5,step6;
int16_t dly1,dly2,dly3,dly4,dly5,dly6;
byte s11,s12,s21,s22,s31,s32,s41,s42,s51,s52,s61,s62;
byte d11,d12,d21,d22,d31,d32,d41,d42,d51,d52,d61,d62;

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int bytesReceived) {
  //done=0;
  s11=Wire.read(); s12=Wire.read(); s21=Wire.read(); s22=Wire.read(); s31=Wire.read(); s32=Wire.read(); s41=Wire.read(); s42=Wire.read(); s51=Wire.read(); s52=Wire.read(); s61=Wire.read(); s62=Wire.read();
  r11=Wire.read(); r12=Wire.read(); r21=Wire.read(); r22=Wire.read(); r31=Wire.read(); r32=Wire.read(); r41=Wire.read(); r42=Wire.read(); r51=Wire.read(); r52=Wire.read(); r61=Wire.read(); r62=Wire.read();
  step1=s11; step1=(step1<<8)|s12; step2=s21; step2=(step2<<8)|s22; step3=s31; step3=(step3<<8)|s32;
  step4=s41; step4=(step4<<8)|s42; step5=s51; step5=(step5<<8)|s52; step6=s61; step6=(step6<<8)|s62;
  dly1=d11; dly1=(dly1<<8)|d12; dly2=d21; dly2=(dly2<<8)|d22; dly3=d31; dly3=(dly3<<8)|d32;
  dly4=d41; dly4=(dly4<<8)|d42; dly5=d51; dly5=(dly5<<8)|d52; dly6=d61; dly6=(dly6<<8)|d62;
    
  Serial.println("Reading");
  Serial.print("STEPS:   ");
  Serial.println(step2);
  Serial.print("RPM:     ");
  Serial.println(dly2);
  
  for(int i=0;i<step2;i++){
    digitalWrite(PUL,HIGH);
    delay(dly2);
    digitalWrite(PUL,LOW);
    delay(dly2);
  }
}
