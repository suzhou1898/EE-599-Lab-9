import random
from datetime import datetime
import time

list = ["INFO","WARN","ERROR","FATAL"]
rand = random.randint(0,1001)

def timer(n):
    while n>0:
        topic = random.sample(list, 1)
        rand = random.randint(0, 1001)
        str1 = "logfile-"
        str2 = datetime.now().strftime("%Y%m%d-%H%M%S")
        str3 = ".txt"
        str4 = str1+str2+str3
        print(str4)
        f = open(str4,'w')
        f.write(topic[0])
        f.write('\n')
        f.write(str(rand))
        n=n-1
        time.sleep(5)

timer(20)








