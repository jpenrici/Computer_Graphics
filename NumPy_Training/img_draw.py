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

    # Desenho
    height = 300
    width = 300

    a = Img(height, width)
    x = width - 1
    y = height - 1

    a.line(0, 0, x, y)
    a.line(x/2, 0, x/2, y, Color.BLUE)
    a.line(0, y, x, 0, Color.GREEN)
    a.line(0, y/4, x, y/4, [127, 127, 127])
    a.line(x/4, y/2, x/2, y/2, c1.getRGB())

    a.circle(x/2, y/2, 25)
    a.circle(x/2, y/2, 50, 90, 180, Color.RED)
    a.circle(x/2, y/2, 75, 180, 270, Color.GREEN)
    a.circle(x/2, y/2, 100, 270, 360, Color.BLUE)

    a.rectangle(100, 100, 20, 20)
    a.rectangle(150, 150, 40, 40, Color.GREEN)
    a.rectangle(220, 220, 50, 50, [255, 64, 32], fill=True)

    a.view()

    print(a.getPixel(x*2, y*2))  # esperado [None, None, None]
    print(a.getPixel(x//2, 0))   # esperado [0, 0, 255]

    # Troca de background
    a.setBackground([255, 127, 0])

    a.export("../Images/draw_1.png")  # esperado fundo colorido


if __name__ == '__main__':

    # Desenhar imagem
    test()
