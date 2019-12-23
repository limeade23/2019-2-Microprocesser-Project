#pragma once

#define buzzer_pin 25


void init_buzzer();
void buzzer_worse();
void buzzer_correct();
void buzzer_close();
void buzzerWrite(int hz);
void buzzer_press(char key);