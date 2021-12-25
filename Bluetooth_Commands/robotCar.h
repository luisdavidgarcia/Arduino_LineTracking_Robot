#ifndef ROBOTCAR_H
#define ROBOTCAR_H

#include <Arduino.h>

class robotCar {
	private:
		const int ENA = 5;
		const int ENB = 6;
		const int IN1 = 7;
		const int IN2 = 8;
		const int IN3 = 9;
		const int IN4 = 11;
		const int Trig = A5;
		const int Echo = A4;
		float distance = 1;
		float velocity = 1.2;
		float degree = 90;
		float objectDistance = 0;

	public:
		robotCar();
		robotCar(float velocity, float distance);
		robotCar(float velocity, float distance, float degree);
		robotCar(float velocity, float distance, float degree, float objectDistance);
		void setUp();
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
		float analogWheelValue();
		unsigned int pingTime();
		float measureDistance();
};		

#endif
