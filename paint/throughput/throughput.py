# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import NullFormatter  # useful for `logit` scale

def loadfile(fileName):
    file=open(fileName)
    node = []
    for line in file:
        # nums = line.strip()
        # node.append(nums[0])
        node.append(line[:-1])
    # print len(file)
    return node



def paint():
    y0 = loadfile("thousand_times_latency.txt")
    x0 = range(1,len(y0)+1)
    y1 = loadfile("thousand_times_latency_energy2.txt")
    y1 = [float(i) for i in y1]
    x1 = range(1, len(y1) + 1)
    y2 = loadfile("thousand_times_latency_energy1.txt")
    y2 = [float(i) for i in y2]
    x2 = range(1, len(y1) + 1)

    plt.figure(figsize=(6, 4))
    plt.plot(x0, y0, 'r--', label="Bare Hedis")
    plt.plot(x1, y1, 'g-', label="Hedis-PWR")
    plt.plot(x2, y2, 'y-.', label="Hedis-PDR")


    plt.xlabel("Time ($t_0$)",fontsize='16')
    plt.ylabel("Throughput",fontsize='16')
    # plt.ylim(0,5000000)
    plt.legend(loc=2, prop={'size': 10})
    plt.yscale('log')
    plt.xscale('log')
    plt.xlim(0,)
    plt.savefig('throughput.eps', format='eps', bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    paint()
