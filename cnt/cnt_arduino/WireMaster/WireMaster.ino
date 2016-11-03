// Wire Master Writer

#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte Step1[2],Step2[2],Step3[2],Step4[2],Step5[2],Step6[2];
byte RPM1[2],RPM2[2],RPM3[2],RPM4[2],RPM5[2],RPM6[2];
uint16_t step1 = 5, step2 = 200, step3 = 1000, step4 = 8000, step5 = 10000, step6 = 20000;
uint16_t rpm1 = 100, rpm2 = 200, rpm3 = 256, rpm4 = 40, rpm5 = 50, rpm6 = 600;
//600 = 2 bytes  //00000010 01011000 (2)(88)
//byte * bytePointer;

void loop() {
  Serial.println("LOOP");
  Wire.beginTransmission(8); // transmit to device #8

  //Splitting every uint16_t step to 2 bytes array
  Step1[0] = (step1>>8)&0xFF; Step1[1] = step1&0xFF;
  Step2[0] = (step2>>8)&0xFF; Step2[1] = step2&0xFF;
  Step3[0] = (step3>>8)&0xFF; Step3[1] = step3&0xFF;
  Step4[0] = (step4>>8)&0xFF; Step4[1] = step4&0xFF;
  Step5[0] = (step5>>8)&0xFF; Step5[1] = step5&0xFF;
  Step6[0] = (step6>>8)&0xFF; Step6[1] = step6&0xFF;
  //Splitting every uint16_t rpm to 2 bytes array
  RPM1[0] = (rpm1>>8)&0xFF; RPM1[1] = rpm1&0xFF;
  RPM2[0] = (rpm2>>8)&0xFF; RPM2[1] = rpm2&0xFF;
  RPM3[0] = (rpm3>>8)&0xFF; RPM3[1] = rpm3&0xFF;
  RPM4[0] = (rpm4>>8)&0xFF; RPM4[1] = rpm4&0xFF;
  RPM5[0] = (rpm5>>8)&0xFF; RPM5[1] = rpm5&0xFF;
  RPM6[0] = (rpm6>>8)&0xFF; RPM6[1] = rpm6&0xFF;

  //Send every 2 bytes array
  Wire.write(Step1,2); Wire.write(Step2,2); Wire.write(Step3,2); Wire.write(Step4,2); Wire.write(Step5,2); Wire.write(Step6,2);
  Wire.write(RPM1,2); Wire.write(RPM2,2); Wire.write(RPM3,2); Wire.write(RPM4,2); Wire.write(RPM5,2); Wire.write(RPM6,2);

  //Stop transmitting
  Wire.endTransmission();

  delay(500);
}
