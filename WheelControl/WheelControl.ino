int ENA = 5, ENB = 6, IN1 = 7, IN2 = 8, IN3 = 9, IN4 = 11;
float distance = 0;
int degRotate = 0;

void setup() {
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

  float velocity = 1.2;
  float analogWheelValue = (velocity - 0.35)/.0075;
  inputSpeed(analogWheelValue,analogWheelValue);
  rightTurn(180,analogWheelValue);
  //forward(5,velocity);

  //velocity = 1.5;
  //analogWheelValue = (velocity - 0.35)/.0075;
  //inputSpeed(analogWheelValue,analogWheelValue);
  //backward(5,velocity);

 // inputSpeed(255,255);
 //calL(analogWheelValue);
  
  while(1);
  
}

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
