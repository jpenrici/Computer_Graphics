# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from scipy import stats

PATH = "./images/"


def test(filename):

    if (filename[-4:] != ".npy"):
        return

    img_np = PATH + filename
    img = np.load(img_np)

    print("Data: ", img_np)
    print("Size: ", img.size)
    print("Shape: ", img.shape)

    height, width, channels = img.shape

    if (channels > 3):
        img = img[:, :, :3]
        print("New Shape: ", img.shape)

    colors = ["RED", "GREEN", "BLUE"]
    for i in range(0, len(colors)):
        # n elementos, mínimo e máximo, média, variância, obliquidade, curtose
        nobs, minmax, mean, variance, skewness, kurtosis = stats.describe(
                img[:, :, i].flatten())
        result = "Scipy[{0}]\nn: {1}\nmin: {2}\nmax: {3}\nmean: {4}\n" \
            "variance:: {5}\nskewness: {6}\nkurtosis: {7}\n"
        print(result.format(colors[i], nobs, minmax[0], minmax[1], mean,
                            variance, skewness, kurtosis))


if __name__ == '__main__':
    test("folha_croton.npy")
