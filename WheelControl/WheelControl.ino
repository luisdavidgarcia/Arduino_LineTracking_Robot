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

  float velocity = 2;
  float analogWheelValue = (velocity - 0.35)/.0075;

  inputSpeed(analogWheelValue,analogWheelValue);
  forward(5,velocity);
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

void backward(float distance, float wheelValue){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //Calculate Velocity for Forward and backward by Using point slope form equation for points at 130 and 255
  float velocity = .0075*wheelValue + .35;
  //calibration from distance to time in ms
  float t = (distance / velocity) * 1000;
  delay(t);
  stopCar();
}

void rightTurn(int deg){  
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //Calibrate from degrees to time in ms (Theta = omega * t)
  float t = (deg / 280.0) * 1000;
  delay(t);
  stopCar();
}

void leftTurn(int deg){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //Calibrate from degrees to time in ms (Theta = omega * t)
  float t = (deg / 260.0) * 1000;
  delay(t);
  stopCar();
}  

void stopCar(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}  
