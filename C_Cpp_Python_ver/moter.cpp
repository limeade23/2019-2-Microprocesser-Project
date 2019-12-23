// function of C++
#include <iostream>
#include <string>
#include <fstream> // file function

// function of C
#include <stdio.h>
#include <time.h>

// function of RaspberryPi
#include <wiringPi.h>
#include <softPwm.h> 

#define SERVO 1 // P18

#include "moter.h"

void init_servo() {
	softPwmCreate(SERVO, 0, 200);
}

void servoOpen() {
	softPwmWrite(SERVO, 12); // 0 degree
}

void servoClose() {
	softPwmWrite(SERVO, 21); // -90degree
}


/*

void servo_nore() {
	softPwmWrite(SERVO, 15);   // 0 degree
	softPwmWrite(SERVO, 24); // 90 degree
	softPwmWrite(SERVO, 5); // -90 degree
}

*/