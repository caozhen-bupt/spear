from numpy import *
import matplotlib.pyplot as plt

fig = plt.figure()

ax = fig.add_subplot(111)
x=[1000,2000,3000]

#plot
ax.barh(arange(len(x)),x,1)

#set ticks
T=arange(len(x))+0.5
ax.set_yticks(T)

#set labels
labels=['a','b','c','d','e']
ax.set_yticklabels(labels)

plt.show()