# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

# módulo de manipulação da imagem
from RGB import *


def test():

    # RGB
    c1 = RGB()
    print(c1.getRGB())  # esperado [255, 255, 255]
    c1.setRGB(-1, 0, 300)
    print(c1.getRGB())  # esperado [0, 0, 255]
    c1.setColor(Color.RED)
    print(c1.getRGB())  # esperado [255, 0, 0]

    print(c1.setColor.__annotations__)
    c1.setColor()                 # ignorado
    c1.setColor(10)               # ignorado
    c1.setColor([0, 1, 2, 3, 4])  # ignorado
    print(c1.getRGB())  # esperado [255, 0, 0]

    # Conversões
    c2 = RGB(255, 127, 64)
    print(c2.toHex())      # esperado #FF7F40
    print(c2.toLong())     # esperado 4227071
    c2.fromLong(16777215)
    print(c2.getRGB())     # esperado [255, 255, 255]
    c2.fromLong(4227071)
    print(c2.getRGB())     # esperado [255, 127, 64]
    c2.fromHex("#FF7F40")
    print(c2.getRGB())     # esperado [255, 127, 64]
    c2.fromHex("#A01E0A")
    print(c2.getRGB())     # esperado [160, 30, 10]


if __name__ == '__main__':
    test()
