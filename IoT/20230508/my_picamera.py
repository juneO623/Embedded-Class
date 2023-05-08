import time
import picamera
from datetime import datetime

camera = picamera.PiCamera()
camera.resolution = (1024, 768)

now = datetime.now()

camera.capture(str(now) + '.jpg')
