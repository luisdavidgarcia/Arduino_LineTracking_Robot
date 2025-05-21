#include "robot_car.hpp"
#include <Arduino.h>

RobotCar::RobotCar() 
{
	setUp();
}	

RobotCar::RobotCar(float velocity, float distance) 
  : velocity(velocity), distance(distance) 
{
	setUp();
}

RobotCar::RobotCar(float velocity, float distance, float degree){
	this->velocity = velocity;
	this->distance = distance;
	this->degree = degree;
	setUp();
}	

RobotCar::RobotCar(float velocity, float distance, float degree, float objectDistance) {
	this->velocity = velocity;
	this->distance = distance;
	this->degree = degree;
	this->objectDistance = objectDistance;
	setUp();
}	

void RobotCar::setUp(){
  pinMode(Trig, OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}	

float RobotCar::analogWheelValue(){
	float analogWheelValue = (velocity - 0.35)/.0075;
	return analogWheelValue;
}	

unsigned int RobotCar::pingTime(){
  unsigned int pingTravelTime = 0;
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig,LOW);
  pingTravelTime = pulseIn(Echo,HIGH);
  return pingTravelTime;
}

float RobotCar::measureDistance(){
  unsigned int pingTravelTime = pingTime();
  float distance_sound = 0, distance_between_objects = 0;
  distance_sound = ((SpeedOFSound * 63360.0 * pingTravelTime)/3600000000.0);
  distance_between_objects = 0.5*distance_sound;
  //distance is in inches
  return distance_between_objects;
}

void RobotCar::pathSquare(int sideLength){
  float analogWheelValue = (velocity - 0.35)/.0075;
  distance = sideLength;
  stopCar();
  delay(100);
  forward();
  delay(100);
  rightTurn();
  forward();
  delay(100);
  rightTurn();
  forward();
  delay(100);
  leftTurn();
  forward();
  delay(100);
  rightTurn();
  delay(100);
  stopCar();
}

void RobotCar::stopCar(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);	
}

void RobotCar::backward(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //calibration from distance to time in ms
  float t = (distance / velocity) * 1000;
  delay(t);
  stopCar();
}

void RobotCar::rightTurn(){
  float analogWheelValue = (velocity - 0.35)/.0075;
  //stop car and delay it to ensure turn occurs smoothly 
  stopCar();
  delay(100);
  //analog value should be smaller for smoother turn
  analogWrite(ENA,130);
  analogWrite(ENB,130);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //Calibrate from degrees to time in ms (Theta = omega * t)
  float t = ((degree + 36)/119.143) * 1000;
  delay(t);
  stopCar();
}

void RobotCar::leftTurn(){
  float analogWheelValue = (velocity - 0.35)/.0075;
  //stop car and delay it to ensure turn occurs smoothly 
  stopCar();
  delay(100);
  //analog value should be smaller for smoother turn
  analogWrite(ENA,130);
  analogWrite(ENB,130);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //Calibrate from degrees to time in ms (Theta = omega * t) using Linear Regression
  float t = ((degree + 36)/119.143) * 1000;
  delay(t);
  stopCar();
} 

void RobotCar::forward(){
float obstacleDistance = 0, targetTime;
  int currentDistance = 0, currentTime, stoppedTime = 0, startTime, initialTimeStop, finalTimeStop;
  bool carBlocked = false;

  startTime = millis();
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  //To Calculate Velocity for Forward and backward by Using point slope form equation for points at 130 and 255
  //float velocity = .0075*wheelValue + .35;

  targetTime = distance/velocity * 1000;
  //Measure current time
  currentTime = millis() - startTime - stoppedTime;

  //loop to for obstacle detection
  while (currentTime <= targetTime){
    currentTime = millis() - startTime - stoppedTime;
    obstacleDistance = measureDistance();
    // loop to check if obstacle is in sight 
    int initialTimeStop = millis();
    while(obstacleDistance <= 12) {
      stopCar();
      //must remeasure or else will be in the loop constantly
      obstacleDistance = measureDistance();
      carBlocked = true;
    }
    int finalTimeStop =  millis();
    if (carBlocked == true) {
      stoppedTime += (finalTimeStop - initialTimeStop);
      //reset carBlocked so that it doesn't repeat loop
      carBlocked = false;
      //turn motors on again 
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
    }
  }                                                                                                                                                                                   
  stopCar();     
}

void RobotCar::inputSpeed(){
  float analogWheelValue = (velocity - 0.35)/.0075;
  analogWrite(ENA,analogWheelValue);
  analogWrite(ENB,analogWheelValue);	
}

void RobotCar::bluetoothCarCommand(char cmd){
 switch(cmd){
    case 'f': {
      forward();
      break;
    }
    case 'b': {
      backward();
      break;
    }
    case 'l': {
      leftTurn();
      break;
    }
    case 'r': {
      rightTurn();
      break;
    }
  }
}	

void RobotCar::bluetoothDistanceReading(char cmd){
switch(cmd){
      case '1': {
        distance = 1;
        break;
      }
      case '2': {
        distance = 2;
        break;       
      }       
      case '3': {
        distance = 3;
        break;       
      }       
      case '4': {
        distance = 4;
        break;       
      }       
      case '5': {
        distance = 5;
        break;       
      }       
      case '6': {
        distance = 6;
        break;       
      }       
      case '7': {
        distance = 7;
        break;       
      }       
      case '8': {
        distance = 8;
        break;       
      }       
      case '9': {
        distance = 9;
        break;       
      }
    }
}

void RobotCar::bluetoothSpeedReading(char cmd) {
switch(cmd){
      case '1': {
        velocity = 1;
        break;
      }
      case '2': {
        velocity = 1.14;
        break;
      }
      case '3': {
        velocity = 1.28;
        break;
      }
      case '4': {
        velocity = 1.42;
        break;
      }
      case '5': {
        velocity = 1.7;
        break;
      }
      case '6': {
        velocity = 1.84;
        break;
      }
      case '7': {
        velocity = 1.98;
        break;                                                                                                                                                        
      }                                                                                                                                                               
      case '8': {                                                                                                                                                     
        velocity = 2.12;                                                                                                                                              
        break;                                                                                                                                                        
      }
      case '9': {
        velocity = 2.26;
        break;
      } 
  }
}	
