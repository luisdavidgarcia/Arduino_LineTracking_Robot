#include "robotCar.h"
char cmd1, buttonSpeed = 's', buttonDistance = 'd', addDegree = '+', subDegree = '-';

robotCar roboCar;

void setup() {
	Serial.begin(9600);
}

void loop() {
  roboCar.inputSpeed();
  while(Serial.available() == 0){}
  cmd1 = Serial.read();
  if (cmd1 == buttonSpeed){
    delay(100);
    while(Serial.available() == 0){}
    cmd1 = Serial.read();
    delay(100);
    roboCar.bluetoothSpeedReading(cmd1);
  }
  if(cmd1 == buttonDistance){
    delay(100);
    while(Serial.available() == 0){}
    cmd1 = Serial.read();
    delay(100);
    roboCar.bluetoothDistanceReading(cmd1);
  }
  roboCar.bluetoothCarCommand(cmd1);
}
