// Wire Slave Receiver

#include <Wire.h>

#define PUL 10
#define DIR 11
#define SlaveID 4
#define StepID step4
#define DelayID dly4
#define NegID neg[3]

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(PUL,LOW);
  digitalWrite(DIR,LOW);
  Wire.begin(SlaveID);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

int16_t step1,step2,step3,step4,step5;
int16_t dly1,dly2,dly3,dly4,dly5;
byte s11,s12,s21,s22,s31,s32,s41,s42,s51,s52;
byte d11,d12,d21,d22,d31,d32,d41,d42,d51,d52;
byte neg[5];

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int bytesReceived) {
  //done=0;
  s11=Wire.read(); s12=Wire.read(); s21=Wire.read(); s22=Wire.read(); s31=Wire.read(); s32=Wire.read(); s41=Wire.read(); s42=Wire.read(); s51=Wire.read(); s52=Wire.read();
  d11=Wire.read(); d12=Wire.read(); d21=Wire.read(); d22=Wire.read(); d31=Wire.read(); d32=Wire.read(); d41=Wire.read(); d42=Wire.read(); d51=Wire.read(); d52=Wire.read();
  neg[0]=Wire.read(); neg[1]=Wire.read(); neg[2]=Wire.read(); neg[3]=Wire.read(); neg[4]=Wire.read();
  step1=s11; step1=(step1<<8)|s12; step2=s21; step2=(step2<<8)|s22; step3=s31; step3=(step3<<8)|s32;
  step4=s41; step4=(step4<<8)|s42; step5=s51; step5=(step5<<8)|s52;
  dly1=d11; dly1=(dly1<<8)|d12; dly2=d21; dly2=(dly2<<8)|d22; dly3=d31; dly3=(dly3<<8)|d32;
  dly4=d41; dly4=(dly4<<8)|d42; dly5=d51; dly5=(dly5<<8)|d52;
    
  Serial.println("Reading");
  Serial.print("STEPS:   ");
  Serial.println(StepID);
  Serial.print("PULSE WIDTH:     ");
  Serial.println(DelayID);
  Serial.print("-VE:     ");
  Serial.println(NegID);
  
  for(int i=0;i<StepID;i++){
    if (NegID==1){
      digitalWrite(DIR,HIGH);
    }
    else if(NegID==0){
      digitalWrite(DIR,LOW);
    }
    digitalWrite(PUL,HIGH);
    delay(DelayID);
    digitalWrite(PUL,LOW);
    delay(DelayID);
  }
}
