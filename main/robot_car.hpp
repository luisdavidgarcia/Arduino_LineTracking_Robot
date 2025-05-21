#ifndef ROBOTCAR_HPP
#define ROBOTCAR_HPP

#include <Arduino.h>

constexpr int ENA = 5;
constexpr int ENB = 6;
constexpr int IN1 = 7;
constexpr int IN2 = 8;
constexpr int IN3 = 9;
constexpr int IN4 = 11;
constexpr int Trig = A5;
constexpr int Echo = A4;
constexpr float SpeedOFSound_MILES_PER_HOUR = 761.0f;
constexpr float VelocityOffset = 0.45f;
constexpr float VelocityScale = 0.0075f;
constexpr float INCHES_PER_MILE = 63360.0f;
constexpr float MICROSECONDS_PER_HOUR = 3600000000.0f;
constexpr float AngularOffsetDegrees = 36.0f;
constexpr float AngularSpeedDegreesPerSec = 119.143f;
constexpr float SecondsToMilliseconds = 1000.0f;
constexpr float ScaleByHalf = 0.5f;
constexpr unsigned int TRIGGER_LOW_DELAY_US = 2;
constexpr unsigned int TRIGGER_HIGH_DELAY_US = 20;
constexpr unsigned int ACTION_DELAY_MS = 100;
constexpr unsigned int MAX_DISTANCE_INCHES = 12;
constexpr unsigned int TURN_PWM_SPEED = 130;

class RobotCar {
private:
	float distance = 1;
	float velocity = 1.2;
	float degree = 90;
	float objectDistance = 0;

	void setUp() const;
	float calculateAnalogWheelValue() const;
	unsigned int pingTime() const;
	void forward() const;
	void backward() const;
	void rightTurn() const;
	void leftTurn() const;	
	void stopCar() const;
	float measureDistance() const;
	
public:
	RobotCar() {setUp();}
	void bluetoothSpeedReading(char cmd);
	void bluetoothDistanceReading(char cmd);
	void bluetoothCarCommand(char cmd);
	void inputSpeed();
	void pathSquare(int sideLengthInches);
};		

#endif // ROBOTCAR_HPP
