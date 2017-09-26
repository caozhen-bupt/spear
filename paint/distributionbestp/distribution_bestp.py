# -*- coding: utf-8 -*-
from __future__ import  division
import numpy as np
import matplotlib.pyplot as plt

def getNeighbor(fileName):
    Array = np.loadtxt(fileName, delimiter=",", usecols=range(1000))
    nbNum = 0
    for i in range(1000):
        for j in range(1000):
            if Array[i][j] == 1:
                nbNum += 1
    return nbNum

def getRangePercent(fileName):
    Array = np.loadtxt(fileName,delimiter=",",usecols=range(1000))

    scale = 10000
    findNum = 0
    notFindNum = 0

    for i in range(1000):
        for j in range(1000):
            if Array[i][j] > 0 and Array[i][j] <= scale:
                findNum += 1
            elif Array[i][j] > scale:
                notFindNum += 1

    return findNum, notFindNum

def calc(neighborFile, file0, file1, file2):
    nbNum = getNeighbor(neighborFile)
    findNum0, notFindNum0 = getRangePercent(file0)
    findNum1, notFindNum1 = getRangePercent(file1)
    findNum2, notFindNum2 = getRangePercent(file2)
    print findNum0, notFindNum0
    print  findNum1, notFindNum1
    print  findNum2, notFindNum2
    print nbNum
    print (findNum0+notFindNum0)/nbNum, (findNum1+notFindNum1)/nbNum,(findNum2+notFindNum2)/nbNum
    # print (findNum0) / nbNum, (findNum1) / nbNum, (findNum2) / nbNum
    return [(findNum0+notFindNum0)/nbNum, (findNum1+notFindNum1)/nbNum, (findNum2+notFindNum2)/nbNum]


def paint():
    label = ("Hedis","Hello","Searchlight", "U-Connect")
    labelCall = np.arange(len(label))

    list = []
    list.append(calc("hedis/neighbor_mod1.txt", "hedis/thousand_mod0_latency.txt", "hedis/thousand_mod1_latency.txt", "hedis/thousand_mod2_latency.txt"))
    list.append(calc("hello/neighbor_mod1.txt", "hello/thousand_mod0_latency.txt", "hello/thousand_mod1_latency.txt", "hello/thousand_mod2_latency.txt"))
    list.append(calc("searchlight/neighbor_mod1.txt", "searchlight/thousand_mod0_latency.txt", "searchlight/thousand_mod1_latency.txt", "searchlight/thousand_mod2_latency.txt"))
    list.append(calc("uconnect/neighbor_mod1.txt", "uconnect/thousand_mod0_latency.txt", "uconnect/thousand_mod1_latency.txt", "uconnect/thousand_mod2_latency.txt"))
    # list.append(calc("quorum/neighbor_mod1.txt", "quorum/thousand_mod0_latency.txt", "quorum/thousand_mod1_latency.txt", "quorum/thousand_mod2_latency.txt"))
    print list

    noMod = []
    mod1 = []
    mod2 = []
    for i in range(4):
        noMod.append(list[i][0])
        mod1.append(list[i][1])
        mod2.append(list[i][2])
    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    plt.bar(labelCall - 0.2, noMod, label="Bare Protocol", color="b", hatch="/", align="center", width=0.2)
    plt.bar(labelCall, mod1, label="PPR ($p_1=0.4$)", color="r", hatch="X", align="center", width=0.2)
    plt.bar(labelCall + 0.2, mod2, label="DPR ($p_2=0.2$)", color="c", hatch="o", align="center", width=0.2)
    plt.xticks(labelCall, label, fontsize=14)
    # plt.title("Figure 6")
    # plt.xlabel("Algorithms")
    plt.ylabel("Discovery Rate (%)", fontsize=18)
    plt.ylim(0,1.03)
    ax.set_yticks([0.2,0.3, 0.4,0.5, 0.6, 0.7, 0.8, 1.0])
    ax.set_yticklabels(['20','30', '40', '50','60', '70','80', '100'])
    #plt.legend(bbox_to_anchor=(1.01, 1),loc=2, prop={'size': 10}, borderaxespad=0.)
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=3, mode="expand", borderaxespad=0.)
    plt.savefig('fig_distribution_optimal.eps', format='eps', bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    paint()
