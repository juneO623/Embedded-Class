import tkinter, requests, re

url = "http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2771038000"

response = requests.get(url)

temp = re.findall(r'<temp>(.+)</temp>', response.text)
humi = re.findall(r'<reh>(.+)</reh>', response.text)

textInfo = temp[len(temp)-1] + 'C' + '  ' + humi[len(humi)-1]

window = tkinter.Tk()
window.title("CPU TEMPERATURE")
window.geometry("480x100")
window.resizable(False, False)

label = tkinter.Label(window, text=textInfo, font=('', 30))
label.pack()

window.mainloop()
