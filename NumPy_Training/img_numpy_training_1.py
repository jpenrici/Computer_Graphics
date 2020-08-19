# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from PIL import Image

PATH = "./images/"
RED = 0
GREEN = 1
BLUE = 2


def details(data):

    separator = 10 * '-'
    print(separator)

    height, width, channels = data.shape
    result = "matrix: {0}D\n{1}x{2}x{3} (h: {1}, w: {2}, channels: {3})\n" \
        "Size: {4}\nType: {5}"
    print(result.format(data.ndim, height, width, channels, data.size,
                        data.dtype))

    result = "maximum values: {0}\nmax. values RGB: {1},{2},{3}"
    print(result.format(np.amax(data), np.amax(data[:,:,RED]),
                        np.amax(data[:,:,GREEN]), np.amax(data[:,:,BLUE])))

    result = "minimum values: {0}\nmin. values RGB: {1},{2},{3}"
    print(result.format(np.amin(data), np.amin(data[:,:,RED]),
                        np.amin(data[:,:,GREEN]), np.amin(data[:,:,BLUE])))


def saveImg(filename, data):
    filename = PATH + filename
    img = Image.fromarray(data)
    img.save(filename)
    print("save ", filename)


def test(filename):

    img_np = PATH + filename + ".npy"  # matriz RGB de imagem gerada no GIMP
    print("Data: ", img_np)

    rgba = np.load(img_np)
    details(rgba)

    rgb = rgba[:, :, :3]  # remover alpha
    details(rgb)

    data = np.zeros(rgb.shape, dtype='uint8')
    details(data)

    R = data
    R[:, :, RED] = rgb[:, :, RED]
    saveImg(filename + "_R.png", R)

    G = data
    G[:, :, GREEN] = rgb[:, :, GREEN]
    saveImg(filename + "_G.png", G)

    B = data
    B[:, :, BLUE] = rgb[:, :, BLUE]
    saveImg(filename + "_B.png", B)


if __name__ == '__main__':
    test("folha_croton")