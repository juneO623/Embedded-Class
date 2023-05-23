from flask import Flask
import RPi.GPIO as GPIO

app = Flask(__name__)

ledPin = 14

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(ledPin, GPIO.OUT)
GPIO.output(ledPin, 0)

@app.route('/')
def flask():
	return "hello Flask"

@app.route('/ledon')
def ledOn():
	GPIO.output(ledPin, 1)
	return "<h1> LED ON </h1>"

@app.route('/ledoff')
def ledOff():
	GPIO.output(ledPin, 0)
	return "<h1> LED OFF </h1>"
	
if __name__ == "__main__":
	app.run(host = "0.0.0.0", port = 80)
