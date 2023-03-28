#-*- coding:utf-8 -*-

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(14, GPIO.OUT)

try:
	while True:
		GPIO.output(14, True)
		sleep(0.5)
		GPIO.output(14, False)
		sleep(0.5)

except KeyboardInterrupt:
	GPIO.cleanup()
