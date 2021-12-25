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
		float degree = 0;
		float objectDistance = 0;

	public:
		robotCar(float velocity, float distance, float degree, float objectDistance);
		void setUp();
		void bluetoothSpeedReading(char cmd);
		void bluetoothDistanceReading(char cmd);
		void bluetoothCarCommand(char cmd);
		void inputSpeed(int tireSpeedLeft, int tireSpeedRight);
		void forward(float distance, float velocity);
		void backward(float distance, float velocity);
		void rightTurn(int degree, float analogWheelValue);
		void leftTurn(int degree, float analogWheelValue);	
		void stopCar();
		void pathSquare(int sideLength, float velocity);
		float analogWheelValue(float velocity);
		unsigned int pingTime();
		float measureDistance();
};		

#endif
