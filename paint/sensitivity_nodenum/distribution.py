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

    scale = 2000
    findNum = 0
    notFindNum = 0

    for i in range(1000):
        for j in range(1000):
            if Array[i][j] > 0 and Array[i][j] <= scale:
                findNum += 1
            elif Array[i][j] > scale:
                notFindNum += 1

    return findNum, notFindNum

def paint():
    neighborFile = ""
    getNeighbor







if __name__ == '__main__':
