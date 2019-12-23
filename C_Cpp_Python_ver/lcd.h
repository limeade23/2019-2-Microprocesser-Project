#pragma once
using namespace std;

int lcdSetup();

void init_lcd(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(const char* s);
void typeChar(char val);

// Lcd Light Relay Setting

void lcdLightOn();
void lcdLightOff();

void lcdOpen();
void lcdOpenString(string name);
void lcdClose();
void lcdWrong();