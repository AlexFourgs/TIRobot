import matplotlib.pyplot as plt
from numpy import genfromtxt
import numpy as np

def main():
    my_data = genfromtxt('capture2.csv', delimiter=',')

    threshold = []
    fps = []

    print(my_data)
    for threshold_tmp, fps_tmp in my_data:
        print(threshold_tmp)
        threshold.append(threshold_tmp)
        fps.append(fps_tmp)

    print(threshold)
    print(fps)

    plt.scatter(threshold, fps)
    
    plt.show()


if __name__ == '__main__':
    main()