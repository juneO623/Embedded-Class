from flask import Flask, render_template, request
import RPi.GPIO as GPIO

app = Flask(__name__)

ledPin = 14

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(ledPin, GPIO.OUT)
GPIO.output(ledPin, 0)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/data', methods=['POST'])
def led():
	led_action = request.form['led']
	if led_action == 'on':
		GPIO.output(ledPin, 1)
		return render_template('index.html')
	else:
		GPIO.output(ledPin, 0)
		return render_template('index.html')

if __name__ == '__main__':
	app.run(host = "0.0.0.0", port = 80)
