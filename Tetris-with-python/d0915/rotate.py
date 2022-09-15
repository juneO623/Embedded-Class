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

def make_block(color):
    for j in range(0, 4):
        for i in range(0,4):
            if block_L[rotate,j,i] == 1:
                gotoxy(i+x, j+y)
                print("\033[%dm" % color + "*" + "\033[0m")
                #print("*")
        print("")
        
def delete_block():
    for j in range(0, 4):
        for i in range(0,4):
            if block_L[rotate,j,i] == 1:
                gotoxy(i+x, j+y)
                print("-")
        print("")
        
        
def overlap_check(tmp_x, tmp_y):
    
    temp_background = background[y+tmp_y:y+tmp_y+4, x+tmp_x:x+tmp_x+4]
    
    if temp_background.shape != block_L[rotate].shape:
        return False
    if np.sum(block_L[rotate,:,:] & temp_background) > 0:
        return False
    
    return True

def overlap_check_sum(xx, yy):
    overlap_count = 1
    if ((x + xx) >= 0) and ((x + xx) <= 8) and ((y + yy <= 18)):
        tmp_back = background[0 + y + yy : 4 + y + yy, 0 + x + xx : 4 + x + xx]
        overlap_block = (tmp_back & block_L[rotate])
        overlap_count = overlap_block.sum()
    return overlap_count

def overlap_check_rotate():
    overlap_count = 1
    tmp_rotate = rotate
    tmp_rotate += 1
    if tmp_rotate == 4:
        tmp_rotate = 0
    
    if (x >= 0) and (x <= 8) and (y <= 18):
        tmp_back = background[0+y:4+y,0+x:4+x]
        overlap_block = (tmp_back & block_L[tmp_rotate])
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

"""
block_L = np.array([[0,0,0,0],
                    [0,1,0,0],
                    [0,1,1,1],
                    [0,0,0,0]])
"""
block_L = np.array([[[0,0,0,0],
                    [0,1,0,0],
                    [0,1,1,1],
                    [0,0,0,0]],
                   
                   [[0,0,0,0],
                    [0,1,1,0],
                    [0,1,0,0],
                    [0,1,0,0]],
                   
                   [[0,0,0,0],
                    [1,1,1,0],
                    [0,0,1,0],
                    [0,0,0,0]],
                   
                   [[0,0,1,0],
                    [0,0,1,0],
                    [0,1,1,0],
                    [0,0,0,0]]])

rotate = 0
      
x = 3
y = 3
           
count = 0             
#print(background.shape)

text_color = np.array([30, 31, 32, 33, 34, 35, 36, 37])

time.sleep(1)    

cls()
draw_background()
make_block(text_color[1])
                                       
while True:
    
    if msvcrt.kbhit():
        key = msvcrt.getch()
        
        if key == b'a':
            #if overlap_check(-1, 0):
            if overlap_check_sum(-1, 0) == 0:
                delete_block()
                x -= 1
                make_block(text_color[1])
                #print(block_L.shape)
            
        elif key == b'd':
            #if overlap_check(1, 0):
            if overlap_check_sum(1, 0) == 0:
                delete_block()
                x += 1
                make_block(text_color[1])
            
        elif key == b's':
            #if overlap_check(0, 1):
            if overlap_check_sum(0, 1) == 0:
                delete_block()
                y += 1
                make_block(text_color[1])
                
        elif key == b'r':
            if overlap_check_rotate() == 0:
                delete_block()
                rotate += 1
                if rotate == 4:
                    rotate = 0
                make_block(text_color[1])
    
    # --------------------------------------------------------
    if count == 100:
        count = 0
        #if overlap_check(0, 1):
        if overlap_check_sum(0, 1) == 0:
            delete_block()
            y += 1
            make_block(text_color[1])
        
    # --------------------------------------------------------
    count += 1
    time.sleep(0.01)
       
    
    
