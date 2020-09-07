# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import os
import numpy as np
from matplotlib import pyplot as plt

PATH = "../Images/"
RED = 0
GREEN = 1
BLUE = 2
ALL = 3


def view(data, channel=ALL, title="histogram"):

    R = data[:, :, RED].flatten()
    G = data[:, :, GREEN].flatten()
    B = data[:, :, BLUE].flatten()

    bins = np.arange(0, 256)
    kwargs = dict(histtype='step', bins=bins)

    if (channel == RED or channel == ALL):
        plt.hist(R, color='r', label="RED", **kwargs)

    if (channel == GREEN or channel == ALL):
        plt.hist(G, color='g', label="GREEN", **kwargs)

    if (channel == BLUE or channel == ALL):
        plt.hist(B, color='b', label="BLUE", **kwargs)

    plt.title(title)
    plt.legend(loc="upper right")
    plt.ylabel('Frequency')
    plt.xlabel('Value')
    plt.show()


def test(filename):

    img_np = PATH + filename + ".npy"
    print("Data: ", img_np)

    if not os.path.exists(img_np):
        print("File not found!")
        return

    data = np.load(img_np)

    h, w, c = data.shape
    if (c > 3):
        data = data[:, :, :3]

    view(data, RED)
    view(data, GREEN)
    view(data, BLUE)
    view(data)


if __name__ == '__main__':
    test("folha_croton")
