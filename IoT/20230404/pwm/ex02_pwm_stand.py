#-*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False);
GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.OUT)

GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

p = GPIO.PWM(18, 50)

p.start(0)
cnt = 0

try:
	while 1:
		if not GPIO.input(21):
			if cnt >= 3:
				cnt = 0
			else:
				cnt += 1
			time.sleep(0.3)
		
		if cnt == 0:
			GPIO.output(18, False)
		elif cnt == 1:
			p.ChangeDutyCycle(30)
		elif cnt == 2:
			p.ChangeDutyCycle(60)
		elif cnt == 3:
			p.ChangeDutyCycle(100)			
				

except KeyboardInterrupt:
	pass
	p.stop()
	GPIO.cleanup()
