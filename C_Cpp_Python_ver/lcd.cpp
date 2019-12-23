#include <iostream>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>

#include <wiringPiI2C.h>
#include <wiringPi.h>

using namespace std;

// Define some device parameters
#define I2C_ADDR   0x27 // I2C device address

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

#include "lcd.h"
#define lcdRelay 0 // 릴레이 wiringPi GPIO 번호 설정

int fd;  // seen by all subroutines

int lcdSetup() {

	fd = wiringPiI2CSetup(I2C_ADDR);
	pinMode(lcdRelay, OUTPUT); // 릴레이 핀 설정

	init_lcd(); // setup LCD

	ClrLcd();

	lcdLightOn();
	lcdLoc(LINE1);
	typeln("Ready");
	delay(1500);
	ClrLcd();

	lcdLoc(LINE1);
	typeln("DOOR CLOSED");
	delay(1000);
	lcdLightOff();

	return 0;
}

void lcdOpen() {
	ClrLcd();
	lcdLightOn();
	delay(100);
	lcdLoc(LINE1);
	typeln("DOOR OPEN");
	lcdLoc(LINE2);
	typeln("Welcome");
}

void lcdOpenString(string name) {
	string msg = "Welcome ";
	msg += name;
	char msg2[100];
	strcpy(msg2, msg.c_str());

	ClrLcd();
	lcdLightOn();
	delay(100);
	lcdLoc(LINE1);
	typeln("DOOR OPEN");
	lcdLoc(LINE2);
	typeln(msg2);
}

void lcdClose(){
	ClrLcd();
	delay(100);
	lcdLoc(LINE1);
	typeln("DOOR CLOSED");
	delay(500);
}

void lcdWrong() {
	lcdLightOn();
	delay(10);
	lcdLoc(LINE2);
	typeln("WRONG PASSWORD!");
	delay(3000);
	ClrLcd();
	lcdLoc(LINE1);
	typeln("DOOR CLOSED");
	lcdLightOff();
}

// float to string
void typeFloat(float myFloat) {
	char buffer[20];
	sprintf(buffer, "%4.2f", myFloat);
	typeln(buffer);
}

// int to string
void typeInt(int i) {
	char array1[20];
	sprintf(array1, "%d", i);
	typeln(array1);
}

// clr lcd go home loc 0x80
void ClrLcd(void) {
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int line) {
	lcd_byte(line, LCD_CMD);
}

// out char to LCD at current position
void typeChar(char val) {

	lcd_byte(val, LCD_CHR);
}


// 스트링 텍스트 LCD 표시
void typeln(const char* s) {

	while (*s) lcd_byte(*(s++), LCD_CHR);

}

void lcd_byte(int bits, int mode) {

	//Send byte to data pins
	// bits = the data
	// mode = 1 for data, 0 for command
	int bits_high;
	int bits_low;
	// uses the two half byte writes to LCD
	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
	bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

	// High bits
	wiringPiI2CReadReg8(fd, bits_high);
	lcd_toggle_enable(bits_high);

	// Low bits
	wiringPiI2CReadReg8(fd, bits_low);
	lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits) {
	// Toggle enable pin on LCD display
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits | ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
	delayMicroseconds(500);
}


void init_lcd() {
	// Initialise display
	lcd_byte(0x33, LCD_CMD); // Initialise
	lcd_byte(0x32, LCD_CMD); // Initialise
	lcd_byte(0x06, LCD_CMD); // Cursor move direction
	lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
	lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
	lcd_byte(0x01, LCD_CMD); // Clear display
	delayMicroseconds(500);
}

void lcdLightOn() {
	digitalWrite(lcdRelay, 1);
}

void lcdLightOff() {
	digitalWrite(lcdRelay, 0);
}