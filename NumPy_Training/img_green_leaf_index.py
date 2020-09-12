# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

'''
    Experiência de análise de imagem de folhas, usando o IFV.

    Índice de Folha Verde (Green Leaf Index)
    ========================================

          2 × G − R − B
    IFV = --------------
          2 × G + R + B

        # Valores positivos indicam as áreas com tonalidade verde.

    Referência:
    LOUHAICHI,M.; BORMAN,M.M.; JOHNSON,D.E. Spatially located platform
    and aerial photography for documentation of grazing impacts on wheat.
    Geocarto International, Taylor & Francis, v. 16, n. 1, p. 65–70, 2001.
'''

import os
import numpy as np
from PIL import Image

PATH = "../Images/"


def calc(data):

    # Índice de folha verde
    # ifv = lambda R,G,B: (2 * G - R - B) / (2 * G + R + B)
    def ifv(R, G, B):
        return (2 * G - R - B) / (2 * G + R + B)

    # Formatar
    h, w, c = data.shape
    v = data.flatten()

    # Calcular
    ifv_list = [ifv(v[i], v[i + 1], v[i + 2]) for i in range(0, h * w * c, c)]
    points = [int(255 * i) if i > 0 else 0 for i in ifv_list]

    # Reformatar
    npArray = np.array(points).reshape(h, w)  # Tons de Cinza
    npArray = np.uint8(npArray)

    return npArray


def view(data):
    img = Image.fromarray(data)
    img.show()


def saveImg(filename, data):
    filename = PATH + filename
    img = Image.fromarray(data)
    img.save(filename)
    print("save ", filename)


def test(filename):
    img_np = PATH + filename + ".npy"
    print("Data: ", img_np)

    if not os.path.exists(img_np):
        print("File not found!")
        return

    data = np.load(img_np)

    h, w, c = data.shape
    if c > 3:
        data = data[:, :, :3]

    result = calc(data)
    view(result)
    saveImg(filename + "_ifv.png", result)


if __name__ == '__main__':

    # ndArray
    px1 = [0, 255, 0]
    px2 = [255, 255, 255]
    pixels = np.array(px1 * 15 + px2 * 5)
    pixels = np.array(pixels).reshape(5, 4, 3)
    result = calc(pixels)
    print(result)

    # ndArray (Imagem)
    test("folha_cafeeiro_doente")
    test("cheflera_variegata")
