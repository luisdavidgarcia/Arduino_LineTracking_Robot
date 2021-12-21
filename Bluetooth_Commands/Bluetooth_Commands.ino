
int ENA = 5, ENB = 6, IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11;
float velocity = 1.2, distance = 1;
char cmd, buttonSpeed = "*", buttonDistance = "#";


void setup() {
  
  Serial.begin(9600);
  
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
  
  while(Serial.available() == 0){}
  cmd = Serial.read();

    
  if (cmd == buttonSpeed){
    while(Serial.available() == 0){}
    cmd = Serial.read();
    //Reading for Setting Car Speed  
    switch(cmd){
      case '0': {
        velocity = 0.35;
        break;
      }
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
  //Reading for Setting Car Distance
  if(cmd == buttonDistance){
    while(Serial.available() == 0){}
    cmd = Serial.read();
    switch(cmd){
      case '0': {
        distance = 0;
        break;
      }
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
  

//calculations for analogWheelValue
  float analogWheelValue = (velocity - 0.35)/.0075;
  inputSpeed(analogWheelValue,analogWheelValue);
 
 //Reading for Car Direciton 
  switch(cmd){
    case 'f': {
      forward(distance,velocity);
      break;
    }
    case 'b': {
      backward(distance, velocity);
      break;
    }
    case 'l': {
      leftTurn(90,analogWheelValue);
      break;
    }
    case 'r': {
      rightTurn(90,analogWheelValue);
      break;
    }
    
  } 
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
