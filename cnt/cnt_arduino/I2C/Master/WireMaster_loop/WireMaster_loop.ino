// Wire Master Writer

#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte Step1[2],Step2[2],Step3[2],Step4[2],Step5[2],Step6[2];
byte Delay1[2],Delay2[2],Delay3[2],Delay4[2],Delay5[2],Delay6[2];
uint16_t step1 = 500, step2 = 500, step3 = 200, step4 = 200, step5 = 200, step6 = 200;
uint16_t dly1 = 500, dly2 = 500, dly3 = 500, dly4 = 500, dly5 = 500, dly6 = 500;
//600 = 2 bytes  //00000010 01011000 (2)(88)
//byte * bytePointer;

//void callback(){
//  subscribe to steps
//  store them in uint16_t variable
//  transform to 2 bytes array
    //Splitting every uint16_t step to 2 bytes array
    Step1[0] = (step1>>8)&0xFF; Step1[1] = step1&0xFF;
    Step2[0] = (step2>>8)&0xFF; Step2[1] = step2&0xFF;
    Step3[0] = (step3>>8)&0xFF; Step3[1] = step3&0xFF;
    Step4[0] = (step4>>8)&0xFF; Step4[1] = step4&0xFF;
    Step5[0] = (step5>>8)&0xFF; Step5[1] = step5&0xFF;
    Step6[0] = (step6>>8)&0xFF; Step6[1] = step6&0xFF;
    //Splitting every uint16_t rpm to 2 bytes array
    Delay1[0] = (dly1>>8)&0xFF; Delay1[1] = dly1&0xFF;
    Delay2[0] = (dly2>>8)&0xFF; Delay2[1] = dly2&0xFF;
    Delay3[0] = (dly3>>8)&0xFF; Delay3[1] = dly3&0xFF;
    Delay4[0] = (dly4>>8)&0xFF; Delay4[1] = dly4&0xFF;
    Delay5[0] = (dly5>>8)&0xFF; Delay5[1] = dly5&0xFF;
    Delay6[0] = (dly6>>8)&0xFF; Delay6[1] = dly6&0xFF;

//  messageAvailable = 1
//}

//void transmission(byte arrays){
  Wire.beginTransmission(1);
  //Send every 2 bytes array
  Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2); Wire.write(Step6,2);
  Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); Wire.write(Delay6,2);

  //Stop transmitting
  Wire.endTransmission();

  Wire.beginTransmission(2);
  //Send every 2 bytes array
  Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2); Wire.write(Step6,2);
  Wire.write(Delay1,2); Wire.write(Delay2,2); Wire.write(Delay3,2); Wire.write(Delay4,2); Wire.write(Delay5,2); Wire.write(Delay6,2);

  //Stop transmitting
  Wire.endTransmission();
//}

void loop() {
  Serial.println("LOOP");
  //subscribe&callback()
  //if messageAvailabe:
  //  Splitting every uint16_t step to 2 bytes array
  //  transmission()
  //  messageAvailable = 0
  delay(500);
}
