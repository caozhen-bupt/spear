# -*- coding: utf-8 -*-
from __future__ import  division
import numpy as np
import matplotlib.pyplot as plt

def getPvalue(fileName):
    Array = np.loadtxt(fileName,delimiter=",", usecols=range(2))
    y_list=[]
    for i in range(99):
        y_list.append(Array[i][1])
    return y_list

def diff_nodeNum():
    x = range(1,100)
    hedisF1 = 'hedis/mod0_nodenum.txt'
    hedisF2 = 'hedis/mod1_nodenum.txt'
    hedisF3 = 'hedis/mod2_nodenum.txt'
    hedisF4 = 'hedis/mod1_nodenum_0.4.txt'
    hedisF5 = 'hedis/mod2_nodenum_0.2.txt'


    y1 = getPvalue(hedisF1)
    y2 = getPvalue(hedisF2)
    y3 = getPvalue(hedisF3)
    y4 = getPvalue(hedisF4)
    y5 = getPvalue(hedisF5)

    y11=[]
    y22=[]
    y33=[]
    y44=[]
    y55=[]
    # print len(x)
    # print len(y1)
    # print len(y2)
    # print len(y3)
    for i in range(99):
        y11.append(y1[i]/x[i])
        y22.append(y2[i]/x[i])
        y33.append(y3[i]/x[i])
        y44.append(y4[i] / x[i])
        y55.append(y5[i] / x[i])

    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    plt.plot(x, y11, 'rv--', label="Hedis")
    plt.plot(x, y22, 'bo-.', label="Hedis-PPR (${p_1}$=0.5)")
    plt.plot(x, y44, 'y+-.', label="Hedis-PPR (${p_1}$=0.4)")
    plt.plot(x, y33, 'gx:', label="Hedis-DPR (${p_2}$=0.5)")
    plt.plot(x, y55, 'm^:', label="Hedis-DPR (${p_2}$=0.2)")
    # plt.plot(x, getPvalue(hedisF4), 'r*-', label="duty cycle = 0.4")
    # plt.plot(x, getPvalue(hedisF5), 'mx-', label="duty cycle = 0.5")
    plt.xlabel("Number of Neighbors: $|N_c|$", fontsize='12')
    plt.ylabel("Discovery Rate (%)", fontsize='12')
    # plt.title("Figure ...")
    plt.ylim(0, 1)
    plt.xlim(1,99)
    plt.legend(loc=1, prop={'size': 10})
    ax.set_yticks([0, 0.2, 0.4, 0.6, 0.8, 1.0])
    ax.set_yticklabels(['0','20', '40', '60', '80', '100'])
    plt.savefig('nodenum.eps', format='eps', bbox_inches='tight')
    plt.show()


if __name__ == '__main__':
    diff_nodeNum()