'''
pad4pi 를 이용하여 동작
pip3 install pad4pi

참고 https://www.raspberrypi.org/forums/viewtopic.php?t=215325
'''

from pad4pi import rpi_gpio
import time
import function as fn

passwd = "1245" # 비밀번호
code = ""

# Setup Keypad
KEYPAD = [
        ["1","2","3","A"],
        ["4","5","6","B"],
        ["7","8","9","C"],
        ["*","0","#","D"]
]

ROW_PINS = [4, 14, 15, 17] # BCM numbering
COL_PINS = [18, 27, 22, 23] # BCM numbering

factory = rpi_gpio.KeypadFactory()

keypad = factory.create_keypad(keypad=KEYPAD, row_pins=ROW_PINS, col_pins=COL_PINS)

class doKey:
    def __init__(self):
       # 입력 저장
        self.pressed_keys = []

    def start(key):
        global code # 입력한 키 저장
        global passwd

        code += key
        print(code)
        if (len(code) == 4):
            if (code == passwd):
                print('Unlock')
                fn.unlock()  # 문열기
                code = ""
            elif key == '#':
                print('Clean')  # '#'를 누르면 초기화
                code = ""
            else:
                print("Invalid")
                fn.wrongLED()  # 빨간 LED 작동
                code = ""
        elif key == '#':
            print('Clean')  # '#'를 누르면 초기화
            code = ""

keys = doKey()
keypad.registerKeyPressHandler(doKey.start)

try:
    while (True):
        time.sleep(0.2)
except:
    keypad.cleanup()
