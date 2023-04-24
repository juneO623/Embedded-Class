#-*-coding:utf-8-*-

# 필요한 라이브러리를 불러옵니다.
import RPi.GPIO as GPIO
import time
import math

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#센서에 연결한 Trig와 Echo 핀의 번호 설정
TRIG = 16
ECHO = 20

BUZZ = 21
print("Distance measurement in progress")

#Trig와 Echo 핀의 출력/입력 설정
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)
GPIO.setup(BUZZ, GPIO.OUT)

#Trig핀의 신호를 0으로 출력
GPIO.output(TRIG, False)

# PWM 인스턴스 p를 만들고 GPIO 21번을 PWM 핀으로 설정, 주파수 = 100Hz
p = GPIO.PWM(BUZZ, 100)

# 4옥타브 도~시 , 5옥타브 도의 주파수
Frq = [ 262, 294, 330, 349, 392 ]

print("Waiting for sensor to settle")
time.sleep(2)

p.start(10)

try:
	while True:
		# Triger 핀에 펄스신호를 만들기 위해 1 출력
		GPIO.output(TRIG, True)
		time.sleep(0.00001) # 10μs 딜레이
		GPIO.output(TRIG, False)
		
		# start time
		while GPIO.input(ECHO)==0:
			start = time.time()
		while GPIO.input(ECHO)==1:
			stop = time.time() # Echo 핀 하강 시간
		
		check_time = stop - start
		distance = check_time * 34300 / 2
		if (math.floor(distance) <= 10):
			print("도")
			p.ChangeFrequency(Frq[0])
		elif (math.floor(distance) <= 20):
			print("레")
			p.ChangeFrequency(Frq[1])
		elif (math.floor(distance) <= 30):
			print("미")
			p.ChangeFrequency(Frq[2])
		elif (math.floor(distance) <= 40):
			print("파")
			p.ChangeFrequency(Frq[3])
		elif (math.floor(distance) <= 50):
			print("솔")
			p.ChangeFrequency(Frq[4])
		else:
			p.ChangeFrequency(1)
			
		print("Distance : %.1f cm" % distance)
		time.sleep(0.4) # 0.4초 간격으로 센서 측정
		
except KeyboardInterrrupt:
	print("Measurement stopped by User")
	GPIO.cleanup()
