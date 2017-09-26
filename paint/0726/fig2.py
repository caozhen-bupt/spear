import numpy as np
import matplotlib.pyplot as plt

def getRangePercent(fileName):
    Array = np.loadtxt(fileName,delimiter=",",usecols=range(1000))
    rangeData=[0,0,0,0,0,0]

    b1=50
    b2=100
    b3=500
    b4=1000
    b5=2000

    for i in range(0,999):
        for j in range(0,999):
            if Array[i][j] > 0 and Array[i][j] <= b1:
                rangeData[0]+=1
            elif Array[i][j] > b1 and Array[i][j] <= b2:
                rangeData[1]+=1
            elif Array[i][j] > b2 and Array[i][j] <= b3:
                rangeData[2]+=1
            elif Array[i][j] > b3 and Array[i][j] <= b4:
                rangeData[3]+=1
            elif Array[i][j] > b4 and Array[i][j] <= b5:
                rangeData[4]+=1
            elif Array[i][j] > b5:
                rangeData[5]+=1

    rangeData = [i/2 for i in rangeData]
    total = float(sum(rangeData))
    rangeData = [float(i/total*100) for i in rangeData]
    return rangeData



lable = ("0-50","50-100","100-500","500-1000","1000-2000",">2000")
lableCall = np.arange(len(lable))

helloFile='hello/thousand_times_latency.txt'
quorumFile='quorum/thousand_times_latency.txt'
uconnectFile='uconnect/thousand_times_latency.txt'
hedisFile='hedis/thousand_times_latency.txt'
searchlightFile='searchlight/thousand_times_latency.txt'

plt.bar(lableCall-0.36,getRangePercent(helloFile),label="Hello",color="b",align="center",width=0.18)
plt.bar(lableCall-0.18,getRangePercent(quorumFile),label="Quorum",color="r",align="center",width=0.18)
plt.bar(lableCall,getRangePercent(uconnectFile),label="Uconnect",color="g",align="center",width=0.18)
plt.bar(lableCall+0.18,getRangePercent(hedisFile),label="Hedis",align="center",width=0.18)
plt.bar(lableCall+0.36,getRangePercent(searchlightFile),label="Searchlight",align="center",width=0.18)
plt.xticks(lableCall,lable)
plt.title("Figure 6")
plt.xlabel("Latency Range")
plt.ylabel("Percentage")
plt.legend()
plt.show()
