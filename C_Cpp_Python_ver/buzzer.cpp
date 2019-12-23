#include <wiringPi.h>
#include <softTone.h>
#include "buzzer.h"

void init_buzzer() {
	softToneCreate(buzzer_pin);
}

void buzzer_worse() {
	for (int i = 0; i < 3; i++) {
		softToneWrite(buzzer_pin, 391);
		delay(100);
		softToneWrite(buzzer_pin, 0);
		delay(100);
	}
}

void buzzer_correct() {
	// do mi sol do
	int melody[]{ 261, 329, 391, 523};

	for (int i = 0; i < 4; i++) {
		softToneWrite(buzzer_pin, melody[i]);
		delay(100);
		softToneWrite(buzzer_pin, 0);
		delay(100);
	}
}

void buzzer_close() {
	// do mi sol do
	int melody[]{ 261, 329, 391, 523 };

	for (int i = 3; i >= 0; i--) {
		softToneWrite(buzzer_pin, melody[i]);
		delay(100);
		softToneWrite(buzzer_pin, 0);
		delay(100);
	}
}

void buzzerWrite(int hz) {
	softToneWrite(buzzer_pin, hz);
	delay(50);
	softToneWrite(buzzer_pin, 0);
	delay(50);
}

void buzzer_press(char key) {
	switch (key) {
	case '1':
		buzzerWrite(261);
		break;
	case '2':
		buzzerWrite(277);
		break;
	case '3':
		buzzerWrite(293);
		break;
	case '4':
		buzzerWrite(311);
		break;
	case '5':
		buzzerWrite(329);
		break;
	case '6':
		buzzerWrite(349);
		break;
	case '7':
		buzzerWrite(369);
		break;
	case '8':
		buzzerWrite(415);
		break;
	case '9':
		buzzerWrite(440);
		break;
	case '0':
		buzzerWrite(466);
		break;
	case '*':
		buzzerWrite(493);
		break;
	case '#':
		buzzerWrite(523);
		break;
	case 'A':
		buzzerWrite(554);
		break;
	case 'B':
		buzzerWrite(587);
		break;
	case 'C':
		buzzerWrite(622);
		break;
	case 'D':
		buzzerWrite(659);
		break;
	}
}