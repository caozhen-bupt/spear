# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

# def figure11_twoNode():
#     x = [0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5]
#     y_hedis = [29, 23, 14, 13, 11, 10, 8, 9, 8]
#     y_hello = [64, 11, 7, 5, 3, 4, 2, 4, 3]
#     y_quorum = [31, 17, 10, 9, 7, 7, 4, 4, 4]
#     y_searchlight = [9, 6, 5, 4, 4, 4, 1, 2, 2]
#     y_uconnect = [17, 19, 12, 4, 6, 3, 3, 3, 3]

#     plt.figure(figsize=(6, 4))
#     plt.plot(x, y_hedis, 'bo--', label="hedis")
#     plt.plot(x, y_hello, 'cv-.', label="hello")
#     plt.plot(x, y_quorum, 'gs:' ,label="quorum")
#     plt.plot(x, y_searchlight,'r*-',  label="searchlight")
#     plt.plot(x, y_uconnect, 'mx-', label="uconnect")
#     plt.ylim(0,65)
#     plt.xlabel("theta")
#     plt.ylabel("latency")
#     plt.title("Figure 1")
#     plt.legend(loc=1, prop={'size': 10})
#     plt.show()
#
# def figure12_twoNodeSym():
#     x = [0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5]
#     y_hedis = [100,47,34,11,12,6,6,6,7]
#     y_hello = [182, 17, 10, 5, 3, 3, 4, 3, 3]
#     y_quorum = [108, 36, 16, 15, 6, 7, 2, 2, 2]
#     y_searchlight = [70,24,18,4,5,2,2,2,2]
#     y_uconnect = [25, 30, 9, 4, 5, 5, 1, 1, 1]
#     plt.figure(figsize=(6, 4))
#     plt.plot(x, y_hedis, 'bo--', label="hedis")
#     plt.plot(x, y_hello,'cv-.', label="hello")
#     plt.plot(x, y_quorum,'gs:' , label="quorum")
#     plt.plot(x, y_searchlight, 'r*-', label="searchlight")
#     plt.plot(x, y_uconnect,'mx-', label="uconnect")
#     plt.ylim(0, 185)
#     plt.xlabel("theta")
#     plt.ylabel("latency")
#     plt.title("Figure 2")
#     plt.legend(loc=1, prop={'size': 8})
#     plt.show()

# def figure13_star_dutycycle():
#     x_hedis0 = [1, 2, 3, 4]
#     x_hedis1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
#     x_hedis2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
#     y_hedis0 = [0.3,0.3,0.3,0.3]
#     y_hedis1 = [0.22521,0.15042,0.107682,0.077766,0.052836,0.037086,0.026004,0.018522,0.012981,0.009192,0.006519,0.004578,0.003216,0.00225,0.001575,0.001104,0.000771,0.00054,0.000381,0.00027]
#     y_hedis2 = [0.3,0.21,0.1029,0.078204,0.0655473,0.035292,0.024702,0.017289,0.008469,0.005928,0.004149,0.002904,0.002031,0.001419,0.000993,0.000693,0.0006,0.0006,0.0006,0]
#     # print y_hedis2.len()
#     x_uconnect0 = [1, 2, 3,4]
#     x_uconnect1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
#     x_uconnect2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
#
#     y_uconnect0 = [0.3,0.3,0.3,0.3]
#     y_uconnect1 = [0.216588, 0.155787, 0.11556, 0.081903, 0.058674, 0.039426, 0.027396, 0.018942, 0.013281, 0.009288, 0.00648, 0.004497, 0.003096, 0.001752, 0.000117]
#     y_uconnect2 = [0.3,0.147,0.1029,0.07203,0.050421,0.024702,0.017289,0.012102,0.005928,0.004149,0.002904,0.001419]
#
#     plt.figure(figsize=(6, 4))
#     # plt.plot(x_hedis0, y_hedis0, label="hedis0")
#     # plt.plot(x_hedis1, y_hedis1, label="hedis1")
#     # plt.plot(x_hedis2, y_hedis2, label="hedis2")
#     plt.plot(x_uconnect0, y_uconnect0, 'gs:',label="uconnect0")
#     plt.plot(x_uconnect1, y_uconnect1, 'r*-',label="uconnect1")
#     plt.plot(x_uconnect2, y_uconnect2, 'mx-',label="uconnect2")
#     plt.ylim(0, 0.32)
#     plt.xlim(1, 20)
#     plt.xlabel("life cycle")
#     plt.ylabel("duty cycle")
#     plt.title("Figure 3")
#     plt.legend(loc=1, prop={'size': 8})
#     plt.show()

# def figure13_star_percentage():
#     x_hedis0 = [1,2,3,4]
#     x_hedis1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
#     x_hedis2= [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
#     y_hedis0 = [0.75042,0.50084,0.25126,0.005706]
#     y_hedis1 = [0.7507,0.5014,0.35894,0.25922,0.17612,0.12362,0.08668,0.06174,0.04327,0.03064,0.02173,0.01526,0.01072,0.0075,0.00525,0.00368,0.00257,0.0018,0.00127,0.0009]
#     y_hedis2 = [0.75011,0.50022,0.33363,0.23368,0.16704,0.11945,0.07186,0.04686,0.02932,0.01742,0.0115,0.00733,0.00444, 0.00303,0.00204,0.00135,0.00075,0.00015,7.05e-005,0]
#
#     x_uconnect0=[1,2,3,4]
#     x_uconnect1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
#     x_uconnect2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
#     y_uconnect0 = [0.72192,0.44384,0.16576,0]
#     y_uconnect1 = [0.72071, 0.51713, 0.3852, 0.27301, 0.19558, 0.13142, 0.09132,0.06314,0.04427,0.03096,0.0216,0.01499,0.01032,0.00584,0.00039]
#     y_uconnect2 = [0.7214, 0.345031,0.242304,0.148954, 0.0909906,0.0520247, 0.0339458, 0.0211438,0.0132623, 0.0082457,0.0049125,0.0014272]
#
#     plt.figure(figsize=(6, 4))
#     plt.plot(x_hedis0, y_hedis0,  'rs--',label="hedis0")
#     plt.plot(x_hedis1, y_hedis1,  'r*:',label="hedis1")
#     plt.plot(x_hedis2, y_hedis2,  'rx-',label="hedis2")
#
#     plt.plot(x_uconnect0, y_uconnect0, 'gs--', label="uconnect0")
#     plt.plot(x_uconnect1, y_uconnect1, 'g*:', label="uconnect1")
#     plt.plot(x_uconnect2, y_uconnect2, 'gx-', label="uconnect2")
#
#     plt.xlim(1, 20)
#     plt.ylim(0,0.8)
#     plt.xlabel("life cycle")
#     plt.ylabel("energy percentage")
#     plt.title("Figure 4")
#     plt.ylim(0,1)
#     plt.legend(loc=1, prop={'size': 8})
#     plt.show()

# def figure13_star_percentage_2T():
#     lable = ("Hedis", "U-Connect", "SearchLight", "Quorum", "Hello")
#     lableCall = np.arange(len(lable))
#
#     b1=[0.501857,0.331939,0.280288,0.283448,0.365882]
#     b2=[0.502786,0.388343,0.400617,0.377385,0.502387]
#     b3=[0.502626,0.35819,0.344487,0.377484,0.502726]
#     plt.bar(lableCall-0.2, b1, label="Original", color="b", hatch="/",align="center", width=0.2)
#     plt.bar(lableCall, b2, label="PWR", color="r", hatch="\\",align="center", width=0.2)
#     plt.bar(lableCall+0.2, b3, label="PDR", color="c", hatch="o",align="center", width=0.2)
#
#     plt.xticks(lableCall, lable)
#     # plt.title("Figure 4")
#     plt.xlabel("Algorithms")
#     plt.ylabel("Energy Percentage at 2T")
#     plt.legend(loc=1,prop={'size': 8})
#     plt.show()

def figure13_star_percentage_2T():
    lable = ("Hedis", "Hello", "Searchlight", "U-Connect")
    lableCall = np.arange(len(lable))

    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    b1=[0.501857,0.365882,0.280288,0.331939]
    b2=[0.502626,0.502726,0.344487,0.35819]
    b3=[0.502786,0.502387,0.400617,0.388343]
    plt.bar(lableCall-0.2, b1, label="Bare Protocol", color="b", hatch="/",align="center", width=0.2)
    plt.bar(lableCall, b2, label="PWR", color="r", hatch="X",align="center", width=0.2)
    plt.bar(lableCall+0.2, b3, label="PDR", color="c", hatch="o",align="center", width=0.2)

    plt.xticks(lableCall, lable, fontsize='14')
    # plt.title("Figure 4")
    # plt.xlabel("Algorithms")
    ax.set_yticks([0.1,0.2,0.3, 0.4,0.5, 0.6])
    ax.set_yticklabels(['10','20','30', '40','50','60'])
    plt.ylabel("Remaining Energy at 2T (%)", fontsize='16')
    plt.legend(loc=1,prop={'size': 10})
    plt.savefig('energy_2T.eps', format='eps', bbox_inches='tight')
    plt.show()
# def figure13_star_percentage_3T():
#     lable = ("Hedis", "U-Connect", "SearchLight", "Quorum", "Hello")
#     lableCall = np.arange(len(lable))
#     b1 = [0.253783, 0.122082, 0.123851, 0, 0.0492205]
#     b2 = [0.360722,0.297552,0.285408,0.264237,0.346866]
#     b3 = [0.336833,0.251486,0.222387,0.230217,0.320952]
#
#     plt.bar(lableCall - 0.2, b1, label="Original", color="b", hatch="/",
#             align="center", width=0.2)
#     plt.bar(lableCall, b2, label="PWR", color="r", hatch="\\", align="center",
#             width=0.2)
#     plt.bar(lableCall + 0.2, b3, label="PDR", color="c", hatch="o", align="center",
#             width=0.2)
#
#     plt.xticks(lableCall, lable)
#     # plt.title("Figure 5")
#     plt.xlabel("Algorithms")
#     plt.ylabel("Energy Percentage at 3T")
#     plt.legend(loc=1, prop={'size': 8})
#     plt.show()
#

def figure13_star_percentage_3T():
    lable = ("Hedis", "Hello", "Searchlight", "U-Connect")
    lableCall = np.arange(len(lable))
    b1 = [0.253783, 0.0492205, 0.123851, 0.122082]
    b2 = [0.336833,0.320952,0.222387,0.251486]
    b3 = [0.360722,0.346866,0.285408,0.297552]
    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    plt.bar(lableCall - 0.2, b1, label="Bare Protocol", color="b", hatch="/",
            align="center", width=0.2)
    plt.bar(lableCall, b2, label="PWR", color="r", hatch="X", align="center",
            width=0.2)
    plt.bar(lableCall + 0.2, b3, label="PDR", color="c", hatch="o", align="center",
            width=0.2)

    plt.xticks(lableCall, lable, fontsize='14')
    # plt.title("Figure 5")
    # plt.xlabel("Algorithms")
    plt.ylabel("Remaining Energy at 3T (%)", fontsize='16')
    plt.legend(loc=1, prop={'size': 10})
    ax.set_yticks([0.05,0.1,0.15,0.2,0.25,0.3,0.35, 0.4])
    ax.set_yticklabels(['5','10','15','20','25','30','35', '40'])
    plt.savefig('energy_3T.eps', format='eps', bbox_inches='tight')
    plt.show()

# def figure13_star_percentage_4T():
#     lable = ("Hedis", "U-Connect", "SearchLight", "Hello")
#     lableCall = np.arange(len(lable))
#     b1=[0.005044,0,0,0]
#     b2=[0.261275,0.200023,0.171218,0.244981]
#     b3=[0.237355,0.15876,0.129774,0.220435]
#
#     plt.bar(lableCall - 0.2, b1, label="No Modification", color="b", hatch="/", align="center", width=0.2)
#     plt.bar(lableCall, b2, label="PWR", color="r", hatch="\\", align="center", width=0.2)
#     plt.bar(lableCall + 0.2, b3, label="PDR", color="c", hatch="o", align="center", width=0.2)
#
#     plt.xticks(lableCall, lable)
#     # plt.title("Figure 5")
#     # plt.xlabel("Algorithms")
#     plt.ylabel("Energy Percentage at 4T")
#     plt.legend(loc=1,prop={'size': 8})
#     plt.show()
#
# def figure13_star_latency():
#     x_hedis0 = [1, 2, 3, 4]
#     x_hedis1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,20]
#     x_hedis2 = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,19,20])
#     y_hedis0 = [3110,3110,3110,3110]
#     y_hedis1 = [2623,2623,8359,4812,29812,26919,27381,26423,34326,34921,44686,41721,44106,29451,32934,22878,9876,3529,3582,4767]
#     y_hedis2 = np.array([32,32,5290,4668,7321,8807,9775,16826,15049,22010,17767,22632,7953,6367,6972,1732,666,666,666,166])
#
#     x_uconnect2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
#     x_uconnect0 = [1, 2, 3,4]
#     x_uconnect1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
#     y_uconnect0 = [118,118,118,118]
#     y_uconnect1 = [7,449,4911,5057,3653,8912,10752,12415,13446,16045,20425,16509,15934,9922,4338]
#     y_uconnect2 = [6, 532, 635, 7178, 469, 9101, 3134, 14071, 15960, 15294, 14424, 12394]
#
#     z_hedis0 = np.polyfit(x_hedis0, y_hedis0, 3)
#     z_hedis1 = np.polyfit(x_hedis1, y_hedis1, 3)
#     z_hedis2 = np.polyfit(x_hedis2, y_hedis2, 3)
#     p1_hedis0 = np.poly1d(z_hedis0)
#     p1_hedis1 = np.poly1d(z_hedis1)
#     p1_hedis2 = np.poly1d(z_hedis2)
#     yvals_hedis0 = p1_hedis0(x_hedis0)
#     yvals_hedis1 = p1_hedis1(x_hedis1)
#     yvals_hedis2 = p1_hedis2(x_hedis2)
#
#     z_uconnect0 = np.polyfit(x_uconnect0, y_uconnect0, 3)
#     z_uconnect1 = np.polyfit(x_uconnect1, y_uconnect1, 3)
#     z_uconnect2 = np.polyfit(x_uconnect2, y_uconnect2, 3)
#     p1_uconnect0 = np.poly1d(z_uconnect0)
#     p1_uconnect1 = np.poly1d(z_uconnect1)
#     p1_uconnect2 = np.poly1d(z_uconnect2)
#     yvals_uconnect0 = p1_uconnect0(x_uconnect0)
#     yvals_uconnect1 = p1_uconnect1(x_uconnect1)
#     yvals_uconnect2 = p1_uconnect2(x_uconnect2)
#
#     plt.figure(figsize=(6, 4))
#     # plt.plot(x_hedis0, y_hedis0, 'rs', label="hedis0")
#     # plt.plot(x_hedis1, y_hedis1, 'r*', label="hedis1")
#     # plt.plot(x_hedis2, y_hedis2, 'rx', label="hedis2")
#     plt.plot(x_hedis0, yvals_hedis0, 'rs--', label="hedis0")
#     plt.plot(x_hedis1, yvals_hedis1, 'r*:', label="hedis1")
#     plt.plot(x_hedis2, yvals_hedis2, 'rx-', label="hedis2")
#
#     # plt.plot(x_uconnect0, y_uconnect0, 'gs--', label="uconnect0")
#     # plt.plot(x_uconnect1, y_uconnect1, 'g*:', label="uconnect1")
#     # plt.plot(x_uconnect2, y_uconnect2, 'gx-', label="uconnect2")
#     plt.plot(x_uconnect0, yvals_uconnect0, 'cs--', label="uconnect0")
#     plt.plot(x_uconnect1, yvals_uconnect1, 'c*:', label="uconnect1")
#     plt.plot(x_uconnect2, yvals_uconnect2, 'cx-', label="uconnect2")
#
#     plt.annotate('die',xy=(4,5000),xytext=(4,-5000),arrowprops=dict(arrowstyle="->",connectionstyle="arc3"))
#
#     plt.ylim(0,50000)
#     plt.xlim(1,20)
#     plt.xlabel("life time")
#     plt.ylabel("latency")
#     plt.title("Figure 5")
#     plt.legend(loc=1, prop={'size': 8})
#     plt.show()
#
#
# # collision modification probability is 0.5
# def figure21():
#     x = [0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5]
#     # the probability that hedis finds neighbors is 37/216
#     y1_hedis = [15728, 8447, 7016, 4091, 3854, 3387, 3337, 3173, 3477]
#     y2_hedis = [67744, 69278, 64113, 55993, 55420, 51232, 51793, 45855, 55325]
#     # the probability that hello finds neighbors is 9/216
#     y1_hello = [40679, 17095, 17458, 13310, 13496, 11665, 11769, 12177, 10456]
#     y2_hello = [54408, 26490, 25476, 23668, 21718, 20673, 20457, 21543, 20047]
#     # the probability that searchlight finds neighbors is 14/216
#     # y1_searchlight = [11350, 11678, 6092, 4215, ]
#     # y2_searchlight = []
#     # the probability that quorum finds neighbors is 19/216
#     y1_quorum = [22397, 8207, 5950, 6004, 3798, 3788, 2431, 2554, 2410]
#     y2_quorum = [54543, 39700, 31557, 27143, 19076, 18482,  17883, 15822, 10054]
#     # y1_searchlight =
#     # y2_searchlight =
#     # y1_uconnect =
#     # y2_uconnect =
#
#     plt.figure(figsize=(6,4))
#     plt.plot(x,y1_hedis,label="hedis discovery probability",color="red")
#     plt.plot(x,y2_hedis,label="hedis decreased probability")
#     plt.plot(x, y1_hello, label="hello discovery probability")
#     plt.plot(x, y2_hello, label="hello decreased probability")
#     plt.plot(x, y1_quorum, label="quorum discovery probability")
#     plt.plot(x, y2_quorum, 'cx--',label="quorum decreased probability")
#     plt.xlabel("theta")
#     plt.ylabel("latency")
#     plt.title("Figure 7")
#     plt.ylim(0,70000)
#     plt.legend(loc = 1, prop={'size':6})
#     plt.show()
#


def star_lifetime():
    lable = ("Hedis", "Hello", "Searchlight", "U-Connect")
    lableCall = np.arange(len(lable))
    b1 = [358425,349655, 313915, 356496]
    b2 = [1845347,1792095,900753,1200381]
    b3 = [2321528,2085478, 1008054,1484133]

    fig = plt.figure(figsize=(8, 4))
    # ax = fig.add_subplot(111)
    plt.bar(lableCall - 0.2, b1, label="Bare Protocol", color="b", hatch="/", align="center", width=0.2)
    plt.bar(lableCall, b2, label="PWR", color="r", hatch="X", align="center", width=0.2)
    plt.bar(lableCall + 0.2, b3, label="PDR", color="c", hatch="o", align="center", width=0.2)

    plt.xticks(lableCall, lable, fontsize='14')
    # plt.title("Figure 5")
    # plt.xlabel("Algorithms")
    plt.ylabel("Life Time ($t_0$)", fontsize='16')
    plt.legend(loc=1, prop={'size': 12})
    plt.savefig('star_lifetime.eps', format='eps', bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    # figure11_twoNode()
    # figure12_twoNodeSym()

    # figure13_star_dutycycle()
    # figure13_star_percentage()
    # figure13_star_latency()
    # figure21()
    figure13_star_percentage_2T()
    figure13_star_percentage_3T()
    # figure13_star_percentage_4T()
    star_lifetime()
