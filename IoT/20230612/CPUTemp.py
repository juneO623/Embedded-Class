import os, time, tkinter

try:
	window = tkinter.Tk()
	window.title("CPU TEMPERATURE")
	window.geometry("480x100")
	window.resizable(False, False)
	
	while True:
		temp = os.popen(" vcgencmd measure_temp ").readline()
		
		textInfo = temp
		
		label = tkinter.Label(window, text=textInfo, font=('', 30))
		label.pack()
		
		window.update()
		label.pack_forget()
		time.sleep(0.5)
	
except KeyboardInterrupt:
	pass
