#include <IRremote.hpp>

int IRpin = 12;

int ENA = 5, ENB = 6, IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11;
int degRotate = 0;

float velocity = 1.2, distance = 1;


IRrecv IR(IRpin);
decode_results cmd;

void setup() {
 
  Serial.begin(9600);
  IR.enableIRIn();
  IR.blink13(true);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void loop() {
  
  while(IR.decode(&cmd) == 0){}

  double star = 0xFF42BD, poundKey = 0xFF52AD;

  //enter velocity with start and for speed just make a formula using point slope form
  if (cmd.value == star){
    delay(500);
    IR.resume();

    //Have to read again
    while(IR.decode(&cmd)== 0) {}
    delay(100);
    
    switch(cmd.value){
      case 0xFF6897: {
        velocity = 1;
        break;
      }
      case 0xFF9867: {
        velocity = 1.14;
        break;
      }
      case 0XFFB04f: {
        velocity = 1.28;
        break;
      }
      case 0xFF30CF: {
        velocity = 1.42;
        break;
      }
      case 0xFF18E7: {
        velocity = 1.7;
        break;
      }
      case 0xFF7A85: {
        velocity = 1.84;
        break;
      }
      case 0xFF10EF: {
        velocity = 1.98;
        break;
      }
      case 0xFF38C7: {
        velocity = 2.12;
        break;
      }
      case 0xFF5AA5: {
        velocity = 2.26;
        break;
      }
      case 0xFF42BD: {
        velocity = 0.35;
        break;
      }
    }
  }

 

  if (cmd.value == poundKey) {
    delay(500);
    IR.resume();
    while(IR.decode(&cmd)== 0) {}
    delay(100);

    switch(cmd.value){
      case 0xFF6897: {
        distance = 1;
        break;
      }
      case 0xFF9867: {
        distance = 2;
        break;
      }
      case 0XFFB04f: {
        distance = 3;
        break;
      }
      case 0xFF30CF: {
        distance = 4;
        break;
      }
      case 0xFF18E7: {
        distance = 5;
        break;
      }
      case 0xFF7A85: {
        distance = 6;
        break;
      }
      case 0xFF10EF: {
        distance = 7;
        break;
      }
      case 0xFF38C7: {
        distance = 8;
        break;
      }
      case 0xFF5AA5: {
        distance = 9;
        break;
      }
      case 0xFF42BD: {
        distance = 0;
        break;
      }
    }    
  }


  float analogWheelValue = (velocity - 0.35)/.0075;
  inputSpeed(analogWheelValue,analogWheelValue);
  
  switch (cmd.value){
    case 0xFF629D: {
      forward(distance,velocity);
      break;
    }
    case 0xFFC23D: {
      rightTurn(90, analogWheelValue);
      break;
    }
    case 0xFFA857: {
      backward(distance,velocity);
      break;
    }
    case 0xFF22DD: {
      leftTurn(90, analogWheelValue);
      break;
    }
    case 0xFF02FD: {
      stopCar(); 
      break;
    }
  }

  delay(500);
  IR.resume();
  


  

 
  /*
  if (cmd.value == 0xFF629D){forward(1,velocity);}
  if (cmd.value == 0xFFC23D) {rightTurn(90, analogWheelValue);}
  if (cmd.value == 0xFFA857) {backward(1,velocity);}
  if (cmd.value == 0xFF22DD) {leftTurn(90, analogWheelValue);}
  if (cmd.value == 0xFF02FD) {stopCar();}
  */
  //velocity = 1.5;
  //analogWheelValue = (velocity - 0.35)/.0075;
  //inputSpeed(analogWheelValue,analogWheelValue);
  //backward(5,velocity);

 // inputSpeed(255,255);
 //calL(analogWheelValue);
  
  //while(1);
  
}

//Function permits us to input only velocity in our funcitons since the speed will be set.
void inputSpeed(int tireSpeedLeft, int tireSpeedRight){
  analogWrite(ENA,tireSpeedLeft);
  analogWrite(ENB,tireSpeedRight);
}

void forward(float distance, float velocity){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  //To Calculate Velocity for Forward and backward by Using point slope form equation for points at 130 and 255
  //float velocity = .0075*wheelValue + .35;
  
  //calibration from distance to time in ms 
  float t = (distance / velocity) * 1000;
  delay(t);
  stopCar();
}  

void backward(float distance, float velocity){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
  //calibration from distance to time in ms
  float t = (distance / velocity) * 1000;
  delay(t);
  stopCar();
}

void rightTurn(int deg, float analogWheelValue){  
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
  float t = ((deg + 36)/119.143) * 1000;
  delay(t);
  stopCar();
}

void leftTurn(int deg, float analogWheelValue){
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
  float t = ((deg + 36)/119.143) * 1000;
  delay(t);
  stopCar();
}  

void stopCar(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}  

//Functions Based off the Main DC Motor Control Funcitons
void pathSquare(int sideLength, float velocity){
  float analogWheelValue = (velocity - 0.35)/.0075;
  stopCar();
  delay(100);
  forward(sideLength,velocity);
  delay(100);
  rightTurn(90, analogWheelValue);
  forward(sideLength,velocity);
  delay(100);
  rightTurn(90, analogWheelValue);
  forward(sideLength,velocity);
  delay(100);
  leftTurn(90, analogWheelValue);
  forward(sideLength,velocity);
  delay(100);
  rightTurn(90, analogWheelValue);
  delay(100);
  stopCar();
}

//Calibration Functions
void calL(int analogWheelValue){
  stopCar();
  delay(100);
  analogWrite(ENA,130);
  analogWrite(ENB,130);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(3000);
  analogWrite(ENA,analogWheelValue);
  analogWrite(ENB,analogWheelValue); 
  stopCar();
}
