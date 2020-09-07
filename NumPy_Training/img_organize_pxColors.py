# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import os
import numpy as np

PATH = "../Images/"


def organize(data):

    # ndArray
    print("Original:")
    print(data[:2])

    # Preparar, remodelar Array
    height, width, channels = data.shape
    data = data.flatten()     # vetorizar
    temp = [i for i in data]  # lista
    temp = [temp[i:i+channels] for i in range(0, height * width * channels,
            channels)]  # separar pixels novamente

    # Ordenação crescente
    for c in range(0, channels):
        # Ordenar do último canal para o primeiro
        i = channels - c - 1
        temp.sort(key=lambda value: value[i])

    npArray = np.array(temp, dtype=np.uint8)
    npArray = npArray.flatten()                         # abrir
    npArray = npArray.reshape(height, width, channels)  # remodelar

    print("Result:")
    print(npArray[:2])


def test(filename):

    img_np = PATH + filename + ".npy"
    print("Data: ", img_np)

    if not os.path.exists(img_np):
        print("File not found!")
        return

    data = np.load(img_np)

    organize(data)


if __name__ == '__main__':

    # Array
    h, w, c = 5, 4, 3
    numbers = [i for i in range(h*w*c, 0, -1)]
    npArray = np.array(numbers).reshape(h, w, c)
    organize(npArray)

    # ndArray
    test("folha_croton")
