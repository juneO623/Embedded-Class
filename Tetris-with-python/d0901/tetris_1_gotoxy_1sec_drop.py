import msvcrt
import time
import os
import ctypes

#----------------------------------------------
def cls():
    os.system('cls')
     

def gotoxy(x,y):
    ctypes.windll.kernel32.SetConsoleCursorPosition(ctypes.windll.kernel32.GetStdHandle(-11),(((y&0xFFFF)<<0x10)|(x&0xFFFF)))

#----------------------------------------------

x_pos = 5
y_pos = 5

cls()
gotoxy(x_pos, y_pos)
print('*')

while 1:
    if msvcrt.kbhit():
        key = msvcrt.getch()
        # print(key )
        
        if key == b'a':
            gotoxy(x_pos, y_pos)
            print(' ')
            
            x_pos-= 1
            
            gotoxy(x_pos, y_pos)
            print('*')
            
            
        elif key == b'd':
            gotoxy(x_pos, y_pos)
            print(' ')
            
            x_pos+= 1
            
            gotoxy(x_pos, y_pos)
            print('*')
            
        elif key == b's':
            gotoxy(x_pos, y_pos)
            print(' ')
            
            y_pos+= 1
            
            gotoxy(x_pos, y_pos)
            print('*')
             
            
 #----------------------------------------------
           
    time.sleep(0.1)

#----------------------------------------------    
print( 'done' )

