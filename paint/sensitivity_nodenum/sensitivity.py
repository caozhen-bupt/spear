# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

def getPvalue(fileName):
    Array = np.loadtxt(fileName,delimiter=",", usecols=range(2))

    y_list=[]
    for i in range(0,9):
        print Array[i][1]
        y_list.append(Array[i][1])
    return y_list

def sensitivity_p1():
    x=[(i+1)*0.1 for i in range(9)]
    helloFile = 'hello/mod1.txt'
    quorumFile = 'quorum/mod1.txt'
    uconnectFile = 'uconnect/mod1.txt'
    hedisFile = 'hedis/mod1.txt'
    searchlightFile = 'searchlight/mod1.txt'
    plt.figure(figsize=(6, 4))
    plt.plot(x, getPvalue(hedisFile), 'r*-', label="Hedis-PPR")
    plt.plot(x, getPvalue(helloFile), 'bo--', label="Hello-PPR")
    # plt.plot(x, getPvalue(quorumFile), 'cv-.', label="Quorum")
    plt.plot(x, getPvalue(searchlightFile), 'mx-', label="Searchlight-PPR")
    plt.plot(x, getPvalue(uconnectFile), 'gs:', label="U-Connect-PPR")

    plt.xlabel("$p_1$", fontsize='16')
    plt.ylabel("Average Latency", fontsize='16')
    # plt.title("Figure 10 fixed duty cycle 0.3")
    plt.ylim(0, 60000)
    plt.xlim(0.1,0.9)
    plt.legend(loc=2, prop={'size': 10})
    plt.savefig('sensitivity_p1.eps', format='eps', bbox_inches='tight')
    plt.show()


def sensitivity_p1_theta():
    x=[(i+1)*0.1 for i in range(9)]
    F1 = 'uconnect/mod1_theta_1.txt'
    F2 = 'uconnect/mod1_theta_2.txt'
    F3 = 'uconnect/mod1_theta_3.txt'
    F4 = 'uconnect/mod1_theta_4.txt'
    F5 = 'uconnect/mod1_theta_5.txt'

    plt.figure(figsize=(6, 4))
    plt.plot(x, getPvalue(F1), 'bo--', label=r"${\theta_c=0.1}$")
    plt.plot(x, getPvalue(F2), 'cv-.', label=r"${\theta_c=0.2}$")
    plt.plot(x, getPvalue(F3), 'gs:', label=r"${\theta_c=0.3}$")
    plt.plot(x, getPvalue(F4), 'r*-', label=r"${\theta_c=0.4}$")
    plt.plot(x, getPvalue(F5), 'mx-', label=r"${\theta_c=0.5}$")
    plt.xlabel("$p_1$", fontsize='16')
    plt.ylabel("Average Latency", fontsize='16')
    # plt.title("Figure 10 Hedis.")
    plt.ylim(0, 90000)
    plt.xlim(0.1, 0.9)
    plt.legend(loc=2, prop={'size': 10})
    plt.savefig('sensitivity_ppr.eps', format='eps', bbox_inches='tight')
    plt.show()

def sensitivity_p2():
    x=[(i+1)*0.1 for i in range(9)]
    helloFile = 'hello/mod2_theta.txt'
    # quorumFile = 'quorum/mod2.txt'
    uconnectFile = 'uconnect/mod2_theta.txt'
    hedisFile = 'hedis/mod2_theta.txt'
    searchlightFile = 'searchlight/mod2_theta.txt'
    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    plt.plot(x, getPvalue(hedisFile), 'r*-', label="Hedis-DPR")
    plt.plot(x, getPvalue(helloFile), 'bo--',label="Hello-DPR")
    # plt.plot(x, getPvalue(quorumFile), 'cv-.',label="Quorum")
    plt.plot(x, getPvalue(searchlightFile), 'mx-', label="Searchlight-DPR")
    plt.plot(x, getPvalue(uconnectFile), 'gs:',label="U-Connect-DPR")


    plt.xlabel("$p_2$", fontsize='20')
    plt.ylabel("Average Latency ($t_0$)", fontsize='20')
    # plt.title("Figure 11 fixed duty cycle 0.3")
    plt.ylim(0, 8500)
    plt.xlim(0.1, 0.9)
    ax.set_yticks([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000])
    ax.set_yticklabels(["1k", '2k', '3k', '4k', '5k', '6k', '7k', '8k'])
    plt.legend(loc=2, prop={'size': 14})
    plt.savefig('sensitivity_p2.eps', format='eps', bbox_inches='tight')
    plt.show()

def sensitivity_p2_theta():
    x=[(i+1)*0.1 for i in range(9)]
    hedisF1 = 'uconnect/mod2_theta_1.txt'
    hedisF2 = 'uconnect/mod2_theta_2.txt'
    hedisF3 = 'uconnect/mod2_theta_3.txt'
    hedisF4 = 'uconnect/mod2_theta_4.txt'
    hedisF5 = 'uconnect/mod2_theta_5.txt'

    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    plt.plot(x, getPvalue(hedisF1), 'bo--', label=r"${\theta_c=0.1}$")
    plt.plot(x, getPvalue(hedisF2), 'cv-.', label=r"${\theta_c=0.2}$")
    plt.plot(x, getPvalue(hedisF3), 'gs:', label=r"${\theta_c=0.3}$")
    plt.plot(x, getPvalue(hedisF4), 'r*-', label=r"${\theta_c=0.4}$")
    plt.plot(x, getPvalue(hedisF5), 'mx-', label=r"${\theta_c=0.5}$")
    plt.xlabel("$p_2$", fontsize='20')
    plt.ylabel("Average Latency ($t_0$)", fontsize='20')
    # plt.title("Figure 11 Hedis")
    plt.ylim(0, 40000)
    plt.xlim(0.1, 0.9)
    ax.set_yticks([1000, 5000, 10000, 20000, 30000, 40000])
    ax.set_yticklabels(['1k','5k','10k', '20k', '30k', '40k'])

    plt.legend(loc=2, prop={'size': 14})
    plt.savefig('sensitivity_p2_uconnect.eps', format='eps', bbox_inches='tight')
    plt.show()

if __name__ == '__main__':

    # sensitivity_p1()
    sensitivity_p2()
    # sensitivity_p1_theta()
    sensitivity_p2_theta()
