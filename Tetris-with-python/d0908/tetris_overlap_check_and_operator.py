import time
import os
import ctypes
import numpy as np
import msvcrt

def cls():
    os.system('cls')

def gotoxy(x,y):
    ctypes.windll.kernel32.SetConsoleCursorPosition(ctypes.windll.kernel32.GetStdHandle(-11),(((y&0xFFFF)<<0x10)|(x&0xFFFF)))

def draw_background():
    for j in range(0,22):
        for i in range(0,12):
            if background[j,i] == 1:
                print("*", end="")
            else:
                print("-", end="")
        print("")

def make_block():
    for j in range(0, 4):
        for i in range(0,4):
            if block_L[j,i] == 1:
                gotoxy(i+x, j+y)
                print("*")
        print("")
        
def delete_block():
    for j in range(0, 4):
        for i in range(0,4):
            if block_L[j,i] == 1:
                gotoxy(i+x, j+y)
                print("-")
        print("")
        
        
def overlap_check(tmp_x, tmp_y):
    
    temp_background = background[y+tmp_y:y+tmp_y+4, x+tmp_x:x+tmp_x+4]
    
    if temp_background.shape != block_L.shape:
        return False
    if np.sum(block_L[:,:] & temp_background) > 0:
        return False
    
    return True

def overlap_check_sum(xx, yy):
    overlap_count = 1
    if ((x + xx) >= 0) and ((x + xx) <= 8) and ((y + yy <= 18)):
        tmp_back = background[0 + y + yy : 4 + y + yy, 0 + x + xx : 4 + x + xx]
        overlap_block = (tmp_back & block_L)
        overlap_count = overlap_block.sum()
    return overlap_count
    

background = np.array([[1,1,1,1,1,1,1,1,1,1,1,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,0,0,0,0,0,0,0,0,0,0,1],
                       [1,1,1,1,1,1,1,1,1,1,1,1]])

block_L = np.array([[0,0,0,0],
                    [0,1,0,0],
                    [0,1,1,1],
                    [0,0,0,0]])
        
x = 3
y = 3
           
count = 0             
#print(background.shape)

time.sleep(1)    

draw_background()
make_block()
                                       
while True:
    
    if msvcrt.kbhit():
        key = msvcrt.getch()
        
        if key == b'a':
            #if overlap_check(-1, 0):
            if overlap_check_sum(-1, 0) == 0:
                delete_block()
                x -= 1
                make_block()
                #print(block_L.shape)
            
        elif key == b'd':
            #if overlap_check(1, 0):
            if overlap_check_sum(1, 0) == 0:
                delete_block()
                x += 1
                make_block()
            
        elif key == b's':
            #if overlap_check(0, 1):
            if overlap_check_sum(0, 1) == 0:
                delete_block()
                y += 1
                make_block()
    
    # --------------------------------------------------------
    if count == 100:
        count = 0
        #if overlap_check(0, 1):
        if overlap_check_sum(0, 1) == 0:
            delete_block()
            y += 1
            make_block()
        
    # --------------------------------------------------------
    count += 1
    time.sleep(0.01)
       
    
    
