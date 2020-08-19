# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
import pandas as pd

PATH = "./images/"


def test(filename):

    if (filename[-4:] != ".npy"):
        return

    img_np = PATH + filename
    img = np.load(img_np)

    print("Data: ", img_np)
    print("Size: ", img.size)
    print("Shape: ", img.shape)

    height, width, channels = img.shape  # (y, x, z)

    if (channels > 3):
        img = img[:, :, :3]
        print("New Shape: ", img.shape)

    rgb = ['R', 'G', 'B']
    names = ['y', 'x', None]
    index = pd.MultiIndex.from_product([range(height), range(width), rgb],
                                        names=names)

    rgbArrayFlatten = img.flatten()
    df = pd.Series(rgbArrayFlatten, index=index)
    df = df.unstack()
    df = df.reset_index().reindex(columns=['x', 'y'] + rgb)

    print(df)
    print(df.describe())


if __name__ == '__main__':
    test("folha_croton.npy")
