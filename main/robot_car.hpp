#ifndef ROBOTCAR_HPP
#define ROBOTCAR_HPP

#include <Arduino.h>

class RobotCar {
private:
	const int ENA = 5;
	const int ENB = 6;
	const int IN1 = 7;
	const int IN2 = 8;
	const int IN3 = 9;
	const int IN4 = 11;
	const int Trig = A5;
	const int Echo = A4;
	const float SpeedOFSound = 761.0F;
	const float VelocityOffset = 0.45F;
	const float VelocityScale = 0.0075F;
	float distance = 1;
	float velocity = 1.2;
	float degree = 90;
	float objectDistance = 0;
	void setUp() const;
	float calculateAnalogWheelValue() const;

public:
	RobotCar() {setUp();}
	void bluetoothSpeedReading(char cmd);
	void bluetoothDistanceReading(char cmd);
	void bluetoothCarCommand(char cmd);
	void inputSpeed();
	void forward();
	void backward();
	void rightTurn();
	void leftTurn();	
	void stopCar();
	void pathSquare(int sideLength);
	unsigned int pingTime();
	float measureDistance();
};		

#endif // ROBOTCAR_HPP
