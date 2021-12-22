
int ENA = 5, ENB = 6, IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11, Trig = A5, Echo = A4;
float velocity = 1.2, distance = 1, degree = 0, objectDistance = 0;
char cmd, buttonSpeed = 's', buttonDistance = 'd', addDegree = '+', subDegree = '-';

void setup() {
  
  Serial.begin(9600);

  pinMode(Trig,OUTPUT);
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

void loop() {

  //calculations for analogWheelValue
  float analogWheelValue = (velocity - 0.35)/.0075;
  inputSpeed(analogWheelValue,analogWheelValue);
  
  while(Serial.available() == 0){}
  cmd = Serial.read();
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
      leftTurn(degree,analogWheelValue);
      break;
    }
    case 'r': {
      rightTurn(degree,analogWheelValue);
      break;
    }  
  } 
  //Reading for Degree Increment of Car
  if (cmd == addDegree && degree != 180) {degree += 10;}
  //Reading for Degree Decrement
  else if (cmd == subDegree && (degree != 0 || degree <= 180)) {degree -= 10;}
  else {degree = 90;}

  //Reading for Velocity of Car
  if (cmd == buttonSpeed){
    delay(100);
    while(Serial.available() == 0){}
    cmd = Serial.read();
    delay(100);
    //Reading for Setting Car Speed  
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
  //Reading for Setting Car Distance
  if(cmd == buttonDistance){
    delay(100);
    while(Serial.available() == 0){}
    cmd = Serial.read();
    delay(100);
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
}

//Function Provides us with the time of Ping Travel
float pingTime(){
  float pingTravelTime = 0;
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig,LOW);
  pingTravelTime = pulseIn(Echo,HIGH);
  return pingTravelTime;
}
//Function provides us with distance between car and obstacle in inches
float measureDistance(){
  float pingTravelTime = pingTime();
  float distance_sound = 0, distance_between_objects = 0;
  //speed of sound is 761 mi/hr
  distance_sound = ((761.0 * 63360.0 * pingTravelTime)/3600000000.0);
  distance_between_objects = 0.5*distance_sound;
  //distance is in inches
  return distance_between_objects;
}


//Function permits us to input only velocity in our funcitons since the speed will be set.
void inputSpeed(int tireSpeedLeft, int tireSpeedRight){
  analogWrite(ENA,tireSpeedLeft);
  analogWrite(ENB,tireSpeedRight);
}

void forward(float distance, float velocity){
  float objectDistance = 0;
  int calculatedDistance = 0;
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  //To Calculate Velocity for Forward and backward by Using point slope form equation for points at 130 and 255
  //float velocity = .0075*wheelValue + .35;

  objectDistance = measureDistance();
  
  while (distance != calculatedDistance){
    calculatedDistance += 1;
    //calibration from distance to time in ms 
    float t = (calculatedDistance / velocity) * 1000;
    delay(t);
    if(objectDistance <= 2) {stopCar();}
    objectDistance = measureDistance(); 
  }
  
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
