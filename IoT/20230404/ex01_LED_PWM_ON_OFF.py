#-*- coding: utf-8 -*-

# 필요한 라이브러리를 불러옵니다.
import RPi.GPIO as GPIO
import time

# 불필요한 warning 제거, GPIO핀의 번호 모드 설정
GPIO.setwarnings(False);
GPIO.setmode(GPIO.BCM)

# GPIO 18번 핀을 출력으로 설정
GPIO.setup(18, GPIO.OUT)

GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# PWM 인스턴스 p를 만들고 GPIO 18번을 PWM 핀으로 설정, 주파수 = 50Hz
p = GPIO.PWM(18, 50)

p.start(0)	# PWM 시작, 듀티비 = 0

pressed = False

def checkButtonState():
	return not GPIO.input(21)

def buttonToggle():
	global pressed
	pressed = not pressed

try:
	while 1:
		if checkButtonState(): buttonToggle()
		if (pressed == False):
			GPIO.output(18, False)
		else:
			for dc in range(0, 101, 1):
				if (checkButtonState()):
					buttonToggle()
					break
				p.ChangeDutyCycle(dc)
				time.sleep(0.01)
			for dc in range(100, -1, -1):
				if (checkButtonState()):
					buttonToggle()
					break
				p.ChangeDutyCycle(dc)
				time.sleep(0.01)

except KeyboardInterrupt:
	pass
	p.stop()
	GPIO.cleanup()
