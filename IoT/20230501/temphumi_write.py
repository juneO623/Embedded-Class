import time
import Adafruit_DHT
import datetime

sensor = Adafruit_DHT.DHT11

pin = 4

try:
	while True:
		h, t = Adafruit_DHT.read_retry(sensor, pin)
		now = datetime.datetime.now()
		if (h is not None) and (t is not None):
			print("Temperature = {0:0.1f}*C Humidity = {1:0.1f}%".format(t, h))
			print(f'{now}\n')
			f = open('temphumi_note.txt', 'a')
			f.write(str(now) + '\r\n')
			f.close()
			time.sleep(1.0)
		else:
			print("Read error")
		time.sleep(1)

except KeyboardInterrupt:
	print("Terminated by Keyboard");
	
finally:
	print("End of Program")
