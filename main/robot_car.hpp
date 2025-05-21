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
constexpr float SpeedOFSound = 761.0F;
constexpr float VelocityOffset = 0.45F;
constexpr float VelocityScale = 0.0075F;

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
	
public:
	RobotCar() {setUp();}
	void bluetoothSpeedReading(char cmd);
	void bluetoothDistanceReading(char cmd);
	void bluetoothCarCommand(char cmd);
	void inputSpeed();
	void pathSquare(int sideLength);
	float measureDistance();
};		

#endif // ROBOTCAR_HPP
