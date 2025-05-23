#include "robot_car.hpp"
#include <Arduino.h>

void RobotCar::setUp() const {
  pinMode(Echo, INPUT);

  pinMode(Trig, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

float RobotCar::calculateAnalogWheelValue() const {
  return (velocity_ - VelocityOffset) / VelocityScale;
}

unsigned int RobotCar::pingTime() const {
  digitalWrite(Trig, LOW);
  delayMicroseconds(TRIGGER_LOW_DELAY_US);

  digitalWrite(Trig, HIGH);
  delayMicroseconds(TRIGGER_HIGH_DELAY_US);

  digitalWrite(Trig, LOW);

  return pulseIn(Echo, HIGH);
}

float RobotCar::measureDistance() const {
  unsigned int pingTravelTime = pingTime();
  float soundRoundTripDistanceINCH =
      ((SpeedOFSound_MILES_PER_HOUR * INCHES_PER_MILE * pingTravelTime) /
       MICROSECONDS_PER_HOUR);
  return ScaleByHalf * soundRoundTripDistanceINCH;
}

void RobotCar::pathSquare(int sideLengthInches) {
  distance_ = sideLengthInches;

  stopCar();
  delay(ACTION_DELAY_MS);
  forward();
  delay(ACTION_DELAY_MS);
  rightTurn();
  forward();
  delay(ACTION_DELAY_MS);
  rightTurn();
  forward();
  delay(ACTION_DELAY_MS);
  leftTurn();
  forward();
  delay(ACTION_DELAY_MS);
  rightTurn();
  delay(ACTION_DELAY_MS);
  stopCar();
}

void RobotCar::stopCar() const {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void RobotCar::backward() const {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // calibration from distance_ to time in ms
  unsigned int t_Milliseconds = (distance_ / velocity_) * SecondsToMilliseconds;
  delay(t_Milliseconds);
  stopCar();
}

void RobotCar::rightTurn() const {
  // stop car and delay it to ensure turn occurs smoothly
  stopCar();
  delay(ACTION_DELAY_MS);

  // analog value should be smaller for smoother turn
  analogWrite(ENA, TURN_PWM_SPEED);
  analogWrite(ENB, TURN_PWM_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  unsigned int t_Milliseconds =
      ((degree_ + AngularOffsetDegrees) / AngularSpeedDegreesPerSec) *
      SecondsToMilliseconds;
  delay(t_Milliseconds);
  stopCar();
}

void RobotCar::leftTurn() {
  // stop car and delay it to ensure turn occurs smoothly
  stopCar();
  delay(ACTION_DELAY_MS);

  // analog value should be smaller for smoother turn
  analogWrite(ENA, TURN_PWM_SPEED);
  analogWrite(ENB, TURN_PWM_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  unsigned int t_MilliSeconds =
      ((degree_ + AngularOffsetDegrees) / AngularSpeedDegreesPerSec) *
      SecondsToMilliseconds;
  delay(t_MilliSeconds);
  stopCar();
}

void RobotCar::forward() {
  float obstacleDistance = 0;
  int currentDistance = 0, stoppedTime = 0;
  bool carBlocked = false;

  int startTime = millis();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  float targetTime = distance_ / velocity_ * SecondsToMilliseconds;
  int currentTime = millis() - startTime - stoppedTime;

  // loop to for obstacle detection
  while (currentTime <= targetTime) {
    currentTime = millis() - startTime - stoppedTime;
    obstacleDistance = measureDistance();

    // loop to check if obstacle is in sight
    int initialTimeStop = millis();
    while (obstacleDistance <= MAX_DISTANCE_INCHES) {
      stopCar();
      // must remeasure or else will be in the loop constantly
      obstacleDistance = measureDistance();
      carBlocked = true;
    }

    int finalTimeStop = millis();
    if (carBlocked == true) {
      stoppedTime += (finalTimeStop - initialTimeStop);
      // reset carBlocked so that it doesn't repeat loop
      carBlocked = false;
      // turn motors on again
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
  }
  stopCar();
}

void RobotCar::inputSpeed() const {
  float analogWheelValue = calculateAnalogWheelValue();
  analogWrite(ENA, analogWheelValue);
  analogWrite(ENB, analogWheelValue);
}

void RobotCar::bluetoothCarCommand(char cmd) const {
  switch (cmd) {
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

void RobotCar::bluetoothDistanceReading(char cmd) {
  switch (cmd) {
  case '1': {
    distance_ = 1;
    break;
  }
  case '2': {
    distance_ = 2;
    break;
  }
  case '3': {
    distance_ = 3;
    break;
  }
  case '4': {
    distance_ = 4;
    break;
  }
  case '5': {
    distance_ = 5;
    break;
  }
  case '6': {
    distance_ = 6;
    break;
  }
  case '7': {
    distance_ = 7;
    break;
  }
  case '8': {
    distance_ = 8;
    break;
  }
  case '9': {
    distance_ = 9;
    break;
  }
  default: {
    distance_ = 1;
    break;
  }
  }
}

void RobotCar::bluetoothSpeedReading(char cmd) {
  switch (cmd) {
  case '1': {
    velocity_ = 1;
    break;
  }
  case '2': {
    velocity_ = 1.14;
    break;
  }
  case '3': {
    velocity_ = 1.28;
    break;
  }
  case '4': {
    velocity_ = 1.42;
    break;
  }
  case '5': {
    velocity_ = 1.7;
    break;
  }
  case '6': {
    velocity_ = 1.84;
    break;
  }
  case '7': {
    velocity_ = 1.98;
    break;
  }
  case '8': {
    velocity_ = 2.12;
    break;
  }
  case '9': {
    velocity_ = 2.26;
    break;
  }
  default: {
    velocity_ = 1;
    break;
  }
  }
}
