# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import os
import numpy as np
from matplotlib import pyplot as plt

PATH = "./images/"
RED = 0
GREEN = 1
BLUE = 2


def view(data, title="histogram"):

    bins = np.arange(0, 256, 10)
    hist, _ = np.histogram(data, bins)

    # plot
    plt.hist(data, bins)
    plt.title(title)
    plt.show()

    print(hist, bins, sep='\n')


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

    view(data[:, :, RED].flatten())
    view(data[:, :, GREEN].flatten())
    view(data[:, :, BLUE].flatten())


if __name__ == '__main__':
    test("folha_croton")
