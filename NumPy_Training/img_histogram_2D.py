# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import os
import numpy as np
from matplotlib import pyplot as plt, colors as colors

PATH = "../Images/"
RED = 0
GREEN = 1
BLUE = 2


def view(data, X, Y, title="2D histogram"):

    c = ["RED", "GREEN", "BLUE"]

    dataX = data[:, :, X].flatten()
    dataY = data[:, :, Y].flatten()
    bins = np.arange(0, 256)

    # plot
    plt.hist2d(dataX, dataY, bins, norm=colors.LogNorm())
    plt.title(title)
    plt.xlabel(c[X])
    plt.ylabel(c[Y])
    plt.xlim([0, 255])
    plt.ylim([0, 255])
    plt.colorbar()
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

    view(data, RED, GREEN)
    view(data, RED, BLUE)
    view(data, GREEN, BLUE)


if __name__ == '__main__':

    # ndArray (Imagem)    
    test("folha_croton")
