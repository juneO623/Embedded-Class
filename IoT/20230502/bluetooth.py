import serial
import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

LED1_PORT = 16
LED2_PORT = 20
LED3_PORT = 21

GPIO.setup(LED1_PORT, GPIO.OUT)
GPIO.setup(LED2_PORT, GPIO.OUT)
GPIO.setup(LED3_PORT, GPIO.OUT)

bleSerial = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1.0)

try:
	while True:
		#sendData = "I am raspberry 3304 \r\n"
		#bleSerial.write(sendData.encode())
		# time.sleep(1.0)
		receiveData = bleSerial.readline().decode().rstrip();
		if receiveData == "LED1ON":
			GPIO.output(LED1_PORT, GPIO.HIGH)
		elif receiveData == "LED2ON":
			GPIO.output(LED2_PORT, GPIO.HIGH)
		elif receiveData == "LED3ON":
			GPIO.output(LED3_PORT, GPIO.HIGH)
		elif receiveData == "LED1OFF":
			GPIO.output(LED1_PORT, GPIO.LOW)
		elif receiveData == "LED2OFF":
			GPIO.output(LED2_PORT, GPIO.LOW)
		elif receiveData == "LED3OFF":
			GPIO.output(LED3_PORT, GPIO.LOW)

except KeyboardInterrupt:
	pass
	
bleSerial.close()
