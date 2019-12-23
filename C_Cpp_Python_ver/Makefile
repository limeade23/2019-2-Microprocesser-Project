main : main.o lcd.o moter.o keypad.o buzzer.o main.h lcd.h moter.h keypad.h buzzer.h
	g++ -o main main.o lcd.o moter.o keypad.o buzzer.o -lwiringPi -lpthread
main.o : main.cpp
	g++ -c main.cpp
lcd.o : lcd.cpp
	g++ -c lcd.cpp
moter.o : moter.cpp
	g++ -c moter.cpp
keypad.o : keypad.cpp
	g++ -c keypad.cpp
buzzer.o : buzzer.cpp
	g++ -c buzzer.cpp
	
clean : 
	rm -rf main *.o *.gch

