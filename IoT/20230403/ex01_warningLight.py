#-*- coding:utf-8 -*-

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(16, GPIO.OUT)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)

try:
	while True:
		GPIO.output(16, True)
		GPIO.output(20, True)
		GPIO.output(21, True)
		sleep(0.1)
		GPIO.output(16, False)
		GPIO.output(20, False)
		GPIO.output(21, False)
		sleep(0.1)

except KeyboardInterrupt:
	GPIO.cleanup()