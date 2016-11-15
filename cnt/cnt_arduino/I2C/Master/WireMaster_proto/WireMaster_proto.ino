// Wire Master Writer

#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte Step1[2],Step2[2],Step3[2],Step4[2],Step5[2];
byte Delay1[2],Delay2[2],Delay3[2],Delay4[2],Delay5[2];
byte neg[5]={0x00,0x00,0x00,0x00,0x00};
//Steps
int16_t s[5]={0,0,0,0,0};

uint16_t step[5]={0,0,0,0,0};
uint16_t dly1 = 50, dly2 = 50, dly3 = 50, dly4 = 100, dly5 = 50;
int done=0;
//600 = 2 bytes  //00000010 01011000 (2)(88)
//byte * bytePointer;

void loop() {
  Serial.println("LOOP");
  //subscribe&callback()
  //if messageAvailabe:
  //  Splitting every uint16_t step to 2 bytes array
  //  transmission()
  //  messageAvailable = 0
  
  for(int n=0;n<5;n++){
    if(s[n]<0){
      neg[n]=0x01;
    }
    else{
      neg[n]=0x00;
    }
    step[n]=abs(s[n]);
  }
  //Splitting every uint16_t step to 2 bytes array
  Step1[0] = (step[0]>>8)&0xFF; Step1[1] = step[0]&0xFF;
  Step2[0] = (step[1]>>8)&0xFF; Step2[1] = step[1]&0xFF;
  Step3[0] = (step[2]>>8)&0xFF; Step3[1] = step[2]&0xFF;
  Step4[0] = (step[3]>>8)&0xFF; Step4[1] = step[3]&0xFF;
  Step5[0] = (step[4]>>8)&0xFF; Step5[1] = step[4]&0xFF;
  
  //Splitting every uint16_t rpm to 2 bytes array
  Delay1[0] = (dly1>>8)&0xFF; Delay1[1] = dly1&0xFF;
  Delay2[0] = (dly2>>8)&0xFF; Delay2[1] = dly2&0xFF;
  Delay3[0] = (dly3>>8)&0xFF; Delay3[1] = dly3&0xFF;
  Delay4[0] = (dly4>>8)&0xFF; Delay4[1] = dly4&0xFF;
  Delay5[0] = (dly5>>8)&0xFF; Delay5[1] = dly5&0xFF;

  if (done==0){
    Wire.beginTransmission(1);
    Serial.println("Transmitting...");
    //Send every 2 bytes array
    Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2);
    Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); 
    Wire.write(neg,5);
    //Stop transmitting
    Wire.endTransmission();

    Wire.beginTransmission(2);
    Serial.println("Transmitting...");
    //Send every 2 bytes array
    Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2);
    Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); 
    Wire.write(neg,5);
    //Stop transmitting
    Wire.endTransmission();

    Wire.beginTransmission(3);
    Serial.println("Transmitting...");
    //Send every 2 bytes array
    Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2);
    Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); 
    Wire.write(neg,5);
    //Stop transmitting
    Wire.endTransmission();

    Wire.beginTransmission(4);
    Serial.println("Transmitting...");
    //Send every 2 bytes array
    Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2);
    Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); 
    Wire.write(neg,5);
    //Stop transmitting
    Wire.endTransmission();

    Wire.beginTransmission(5);
    Serial.println("Transmitting...");
    //Send every 2 bytes array
    Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2);
    Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); 
    Wire.write(neg,5);
    //Stop transmitting
    Wire.endTransmission();
    done=1;
  }
  delay(500);
}
