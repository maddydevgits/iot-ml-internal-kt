import serial
import time
import pandas as pd

ser=serial.Serial('COM8',9600,timeout=0.5)
dataset=[]
count=0

while True:
    if(ser.inWaiting()>0):
        try:
            data=ser.readline().decode('utf-8')
            if(data.startswith('#')):
                data=data[:-1]
                data=data.split(',')
                dummy=[]
                dummy.append(int(data[1])) # m 
                dummy.append(data[2]) # state
                dummy.append(data[3]) # action
                dataset.append(dummy) # nested list
                count+=1
                if(count==50):
                    df=pd.DataFrame(dataset)
                    df.to_csv("iotdata.csv")
                    count=0
                print("Iterating for {0}".format(count))
        except:
            continue

