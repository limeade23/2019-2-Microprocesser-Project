// function of C++
#include <iostream>
#include <string>
#include <fstream> // file function
#include <ctime>
#include <thread> 

// function of C
#include <stdio.h>
#include <time.h>


#include <wiringPi.h>

// function of ETC
#include "lcd.h"
#include "keypad.h"
#include "buzzer.h"
#include "moter.h"

#include "main.h"

using namespace std;

int main() {

	wiringPiSetup();

	init_keypad();
	init_buzzer();
	init_servo();
	lcdSetup();

	thread sv(socketReceive);

	string pad_passwd = "1245";
	string pad_buff;
	pad_buff.clear(); // 

	while (1)
	{
		char temp = get_key();

		if (temp) { // 버튼을 누른 경우
			pad_buff += temp;
			thread tb(buzzer_press, temp); tb.join(); // 버튼 입력 소리
			if (pad_buff.length() >= 4) { // 4글자 입력했다면
				if (pad_buff.compare(pad_passwd) == 0){
					
					// 글자가 맞으면
					doorOpen();

				}
				else {
					// 틀린 비밀번호
					logs(2, "null");
					thread t1(buzzer_worse);
					thread t2(lcdWrong);
					t1.join();
					t2.join();
				}
				pad_buff.clear(); // 다시 초기화

			}
			/* // 디버깅
			printf("prsss : %c \t press len : %d\n", temp, pad_buff.length());
			cout << "save >> " << pad_buff << endl;
			*/
		}
		else;

		delay(180); // 채터링 방지 딜레이
	}
	sv.join();
	return 0;
}

// 로그 작성기
void logs(int val, string name) {
	time_t curr_time;

	struct tm* ct;
	curr_time = time(NULL);
	ct = localtime(&curr_time);

	string method, sof;

	switch (val) {
	case 1:
		method = "Keypad";
		sof = "Success";
		break;
	case 2:
		method = "Keypad";
		sof = "Fail";
		break;
	case 3:
		method = "Facedetection";
		sof = "Success";
		break;
	default:
		method = "NULL";
		sof = "NULL";
		break;
	}

	ofstream fs("./log.txt", ios::app);
	cout << ct->tm_year + 1900 << " " << ct->tm_mon + 1 << " " << ct->tm_mday << " " << ct->tm_hour << " " << ct->tm_min << " " << ct->tm_sec << "	method : " << method << " - " << sof << " by : " << name << endl;

	if (fs.is_open()) {
		fs << ct->tm_year + 1900 << " " << ct->tm_mon + 1 << " " << ct->tm_mday << " " << ct->tm_hour << " " << ct->tm_min << " " << ct->tm_sec << "	method : " << method << " - " << sof << " by : " << name << endl;
	}

	fs.close();
}

void doorOpen() {
	logs(1, "null");
	thread t1(lcdOpen);
	thread t2(servoOpen);
	thread t3(buzzer_correct);
	t1.join();
	t2.join();
	t3.join();
	delay(3000);
	thread t5(servoClose);
	thread t6(lcdClose);
	thread t7(buzzer_close);
	delay(2000);
	lcdLightOff();
	t5.join();
	t6.join();
	t7.join();
}

void doorOpenSt(string name) {
	logs(3, name);
	thread t1(lcdOpenString, name);
	thread t2(servoOpen);
	thread t3(buzzer_correct);
	t1.join();
	t2.join();
	t3.join();
	delay(3000);
	thread t5(servoClose);
	thread t6(lcdClose);
	thread t7(buzzer_close);
	delay(2000);
	lcdLightOff();
	t5.join();
	t6.join();
	t7.join();
}