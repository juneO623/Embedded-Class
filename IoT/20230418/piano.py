#-*-coding:utf-8-*-

# 필요한 라이브러리를 불러옵니다.
import RPi.GPIO as GPIO
import time

# 불필요한 warning 제거, GPIO핀의 번호 모드 설정
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

BUZZ_PORT = 21

BTN_ONE = 24
BTN_TWO = 23
BTN_THREE = 18
BTN_FOUR = 15
BTN_FIVE = 14

# GPIO 21번 핀을 출력으로 설정
GPIO.setup(BUZZ_PORT, GPIO.OUT)	# Buzz

GPIO.setup(BTN_ONE, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	# 1번 스위치
GPIO.setup(BTN_TWO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	# 2번 스위치
GPIO.setup(BTN_THREE, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	# 3번 스위치
GPIO.setup(BTN_FOUR, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	# 4번 스위치
GPIO.setup(BTN_FIVE, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)	# 5번 스위치

# PWM 인스턴스 p를 만들고 GPIO 21번을 PWM 핀으로 설정, 주파수 = 100Hz
p = GPIO.PWM(21, 100)

# 4옥타브 도~시 , 5옥타브 도의 주파수
Frq = [ 262, 294, 330, 349, 392 ]
speed = 0.5 # 음과 음 사이 연주시간 설정 (0.5초)

p.start(10) # PWM 시작 , 듀티사이클 10 (충분)

try:
	while 1:
		if GPIO.input(BTN_ONE) == GPIO.HIGH:
			p.ChangeFrequency(Frq[0])
		elif GPIO.input(BTN_TWO) == GPIO.HIGH:
			p.ChangeFrequency(Frq[1])
		elif GPIO.input(BTN_THREE) == GPIO.HIGH:
			p.ChangeFrequency(Frq[2])
		elif GPIO.input(BTN_FOUR) == GPIO.HIGH:
			p.ChangeFrequency(Frq[3])
		elif GPIO.input(BTN_FIVE) == GPIO.HIGH:
			p.ChangeFrequency(Frq[4])
		else:
			p.ChangeFrequency(1)

finally:
	p.stop(0)
	GPIO.cleanup()
	
	'''		
except KeyboardInterrupt: # 키보드 Ctrl+C 눌렀을때 예외발생
	pass # 무한반복을 빠져나와 아래의 코드를 실행
	p.stop() # PWM을 종료
	GPIO.cleanup() # GPIO 설정을 초기화
'''
