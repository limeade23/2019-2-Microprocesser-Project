'''
PCA9685를 사용하기에 아래의 커맨드를 사용해야 함
sudo pip3 install adafruit-circuitpython-servokit
'''

import RPi.GPIO as GPIO
import time
from adafruit_servokit import ServoKit

# GPIO 핀 선택
led_G = 13 # Green LED
led_R = 26 # Red LED

GPIO.setmode(GPIO.BCM)
GPIO.setup(led_G, GPIO.OUT)
GPIO.setup(led_R, GPIO.OUT)

kit = ServoKit(channels=16)

def unlock():
    GPIO.output(led_G, True)
    # 모터가 작동되면서 LED 켜짐
    kit.servo[0].angle = 0
    time.sleep(3.0) # 3초간 열리고 닫힘
    kit.servo[0].angle = 180
    # 다시 모터가 작동되면서 LED 꺼짐
    GPIO.output(led_G, False)

def wrongLED():
    GPIO.output(led_R, True) # LED 켜짐
    time.sleep(3.0) # 3초간 작동
    GPIO.output(led_R, False) # LED 꺼짐

