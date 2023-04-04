#-*- coding:utf-8 -*-

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(19, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.output(19, False)
GPIO.output(26, False)

try:
	while True:
		if (not GPIO.input(21)):
			GPIO.output(26, True)
			GPIO.output(19, False)
			sleep(0.1)
			GPIO.output(19, True)
			GPIO.output(26, False)
			sleep(0.1)
		else:
			GPIO.output(19, False)
			GPIO.output(26, False)
			
except KeyboardInterrupt:
	GPIO.cleanup()