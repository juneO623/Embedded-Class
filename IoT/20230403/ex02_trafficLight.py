#-*- coding:utf-8 -*-

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(16, GPIO.OUT)	# 신호 빨강
GPIO.setup(20, GPIO.OUT)	# 신호 노랑
GPIO.setup(21, GPIO.OUT)	# 신호 초록
GPIO.setup(19, GPIO.OUT)	# 보행 빨강
GPIO.setup(26, GPIO.OUT)	# 보행 초

GPIO.output(16, False)
GPIO.output(20, False)
GPIO.output(21, False)
GPIO.output(19, False)
GPIO.output(26, False)

try:
	while True:
		GPIO.output(16, False)
		GPIO.output(26, False)
		GPIO.output(21, True)
		GPIO.output(19, True)
		sleep(3)
		GPIO.output(21, False)
		GPIO.output(19, False)
		GPIO.output(20, True)
		sleep(3)
		GPIO.output(20, False)
		GPIO.output(16, True)
		GPIO.output(26, True)
		sleep(3)

except KeyboardInterrupt:
	GPIO.cleanup()