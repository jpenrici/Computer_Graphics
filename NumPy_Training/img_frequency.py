# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import os
import numpy as np
from random import randrange

# módulo de manipulação da imagem
from RGB import RGB

PATH = "../Images/"


def view(data, num_out_values=10):

    # Formatar
    h, w, c = data.shape
    d = data.flatten()
    rgb_hex = [RGB(int(d[i]), int(d[i+1]), int(d[i+2])).toHex()
               for i in range(0, h * w * c, c)]

    # Contar
    u_hex, counts = np.unique(rgb_hex, return_counts=True)

    # Listar
    ranking = {u_hex[i]: counts[i] for i in range(len(u_hex))}
    ranking = sorted(ranking.items(), key=lambda v: v[1], reverse=True)
    max_pos = num_out_values if num_out_values < len(ranking) else 10

    print("Frequency:")
    print("RGB             Hexa     Integer    Num/Total %")
    for v in ranking:
        percent = v[1] / (h * w)
        print("{} {}{:>10} {:>3}/{} {:.2f}%".format(RGB(v[0]),
              RGB(v[0]).toHex(), RGB(v[0]).toInt(), v[1], str(h * w),
              percent * 100))
        max_pos = max_pos - 1
        if max_pos < 0:
            break
    print("-" * 50)


def test(filename, num_out_values=10):

    img_np = PATH + filename + ".npy"
    print("Data: ", img_np)

    if not os.path.exists(img_np):
        print("File not found!")
        return

    data = np.load(img_np)

    h, w, c = data.shape
    if (c > 3):
        data = data[:, :, :3]

    view(data, num_out_values)


if __name__ == '__main__':

    # ndArray
    px1 = [10, 10, 10]
    px2 = [255, 255, 255]
    pixels = np.array(px1 * 15 + px2 * 5)
    pixels = np.array(pixels).reshape(5, 4, 3)
    view(pixels)

    h, w, c = 5, 4, 3
    pixels = []
    for i in range(h * w):
        r = randrange(0, 255)
        g = randrange(0, 255)
        b = randrange(0, 255)
        pixels += [[r, g, b]]
    pixels = np.array(pixels).reshape(h, w, c)
    view(pixels, 3)

    # ndArray (Imagem)
    test("folha_cafeeiro_doente", 5)
