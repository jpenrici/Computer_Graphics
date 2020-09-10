# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

# módulo de manipulação da imagem
from RGB import *


def test():

    # RGB
    c = RGB()
    assert c.getRGB() == [0, 0, 0]
    c.setRGB(-1, 0, 300)
    assert c.getRGB() == [0, 0, 255]
    c.setColor(Color.RED)
    assert c.getRGB() == [255, 0, 0]

    assert c.setColor.__annotations__ == {'rgb': 'list'}
    c.setColor()                 # ignorado
    c.setColor(10)               # ignorado
    c.setColor([0, 1, 2, 3, 4])  # ignorado
    assert c.getRGB() == [255, 0, 0]

    # Conversões
    c = RGB(255, 0, 0)
    assert c.toHex() == "#FF0000"
    assert c.toInt() == 16711680

    c = RGB(0, 255, 0)
    assert c.toHex() == "#00FF00"
    assert c.toInt() == 65280

    c = RGB(0, 0, 255)
    assert c.toHex() == "#0000FF"
    assert c.toInt() == 255

    c = RGB(255, 127, 64)
    assert c.toHex() == "#FF7F40"
    assert c.toInt() == 16744256
    c.fromInt(16777215)
    assert c.getRGB() == [255, 255, 255]
    c.fromInt(16744256)
    assert c.getRGB() == [255, 127, 64]
    c.fromHex("#FF7F40")
    assert c.getRGB() == [255, 127, 64]
    c.fromHex("#A01E0A")
    assert c.getRGB() == [160, 30, 10]

    c = RGB([10, 10, 10])
    assert c.getRGB() == [10, 10, 10]

    c = RGB("#FF7F40")
    assert c.getRGB() == [255, 127, 64]

    c = RGB(3302420)
    assert c.getRGB() == [50, 100, 20]
    assert c.toHex() == "#326414"
    assert c.toInt() == 3302420

    del c

    print("test ok")


if __name__ == '__main__':
    test()
