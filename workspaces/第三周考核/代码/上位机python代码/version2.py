import serial
import os
import msvcrt
import time
from tkinter import *

ser=serial.Serial(
    port='COM7',
    baudrate=115200 
)

win=Tk()
win.title('控制舵机')
win.geometry("1024x640")
txt=StringVar()#元组类

a=[0,0,0,0,0]
txt=StringVar()
txt2=StringVar()
txt.set('nothing!')

while ser.in_waiting:
    ser.read()

def key_action(event):
    #print("pressed",repr(event.char))#按下时打印在工作台
    strstr=event.char
    ser.write(strstr.encode('utf-8'))
    #time.sleep(30/1000) #nrf出问题就加上延迟
    if ser.in_waiting:
        for i in range(0,5):
            a[i]=ser.read()
            a[i] = int.from_bytes(a[i], byteorder = 'big')
    strstr="舵机1："
    strstr+=str(a[0])+'\n'
    strstr+="舵机2："+str(a[1])+'\n'+"舵机3："+str(a[2])+'\n'+"舵机4："+str(a[3]) +'\n'+'len:'+str(a[4])   
    txt.set(strstr)
    print(a)

def callback(event):
    L.focus_set()#把键盘焦点设置到文本上

L=Label(win,width=80,font=('微软雅黑',50),textvariable=txt,bg='cyan')#按下后显示在lable上
L.bind("<KeyPress>",key_action)
L.bind("<Button-1>",callback)#鼠标点下将回调回来到我点的地方
L.pack()

win.mainloop()

