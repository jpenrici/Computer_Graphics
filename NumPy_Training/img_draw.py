# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from PIL import Image
from math import sqrt, sin, cos, radians


class RGB:

    __rgb = []

    def __init__(self, red=255, green=255, blue=255):

        self.__rgb = self.__config(red, green, blue)

    def __config(self, red, green, blue):

        # Limite inferior
        red = 0 if red < 0 else red
        green = 0 if green < 0 else green
        blue = 0 if blue < 0 else blue

        # Limite superior
        red = 255 if red > 255 else red
        green = 255 if green > 255 else green
        blue = 255 if blue > 255 else blue

        return [red, green, blue]

    def setRGB(self, red, green, blue):

        self.__rgb = self.__config(red, green, blue)

    def setColor(self, rgb: 'list'=None):

        if not isinstance(rgb, list):
            return
        if len(rgb) != 3:
            return

        self.__rgb = self.__config(rgb[0], rgb[1], rgb[2])

    def getRGB(self):

        return self.__rgb


class Color:

    # Cores pré definidas
    RED = [255, 0, 0]
    GREEN = [0, 255, 0]
    BLUE = [0, 0, 255]
    BLACK = [0, 0, 0]
    WHITE = [255, 255, 255]


class Img:

    __channels = 3  # RGB

    def __init__(self, height, width, background=Color.BLACK):

        self.width = width
        self.height = height
        self.background = background

        # Armazenamento em vetor
        self.pixels = np.array(background * height * width, dtype='uint8')

    def __isValid(self, x, y):

        if (x < 0 or x >= self.width):
            return False
        if (y < 0 or y >= self.height):
            return False

        return True

    def setPixel(self, x, y, color=Color.WHITE):

        x = int(x)
        y = int(y)

        if (not self.__isValid(x, y)):
            # Não desenhar fora dos limites
            return

        pos = self.__channels * (x + y * self.width)
        self.pixels[pos:pos+self.__channels] = color

    def getPixel(self, x, y):

        if (not self.__isValid(x, y)):
            return [None, None, None]

        pos = self.__channels * (x + y * self.width)
        pixel = self.pixels[pos:pos+self.__channels]

        return pixel

    def setBackground(self, color=Color.WHITE):

        # Troca de cores do fundo
        stop = self.height * self.width * self.__channels
        for pos in range(0, stop, self.__channels):
            value = self.pixels[pos:pos+self.__channels]
            if (value == self.background).all():
                self.pixels[pos:pos+self.__channels] = color
        self.background = color

    def line(self, x0, y0, x1, y1, color=Color.WHITE):

        x = x1 - x0
        y = y1 - y0
        step_x = -1 * (x < 0) + (x > 0)
        step_y = -1 * (y < 0) + (y > 0)

        d = int(sqrt(x**2 + y**2))
        for i in range(d):
            self.setPixel(x0 + (i * step_x), y0 + (i * step_y), color)

    def circle(self, x0, y0, radius=2, start=0, stop=360, color=Color.WHITE):

        start = 0 if (start < 0 or start > 360) else start
        stop = 360 if (stop < 0 or stop > 360) else stop

        for angle in range(start, stop):
            x = x0 + int(radius * sin(radians(angle)))
            y = y0 + int(radius * cos(radians(angle)))
            self.setPixel(x, y, color)

    def rectangle(self, x0, y0, height=2, width=2, color=Color.WHITE,
                  fill=False):

        if (not fill):
            self.line(x0, y0, x0 + width, y0, color)
            self.line(x0, y0, x0, y0 + height, color)
            self.line(x0 + width, y0, x0 + width, y0 + height, color)
            self.line(x0, y0 + height, x0 + width, y0 + height, color)

        if (fill):
            if (not self.__isValid(x0, y0)):
                return
            if (not self.__isValid(x0 + width, y0 + height)):
                return
            # Preencher
            for y in range(y0, y0 + height):
                pos = self.__channels * (x0 + y * self.width)
                self.pixels[pos:pos + self.__channels * width] = color * width

    def view(self):

        output = self.pixels.reshape(self.height, self.width, self.__channels)
        # print(output)

        display = Image.fromarray(output, 'RGB')
        display.show()

    def export(self, filename):

        output = self.pixels.reshape(self.height, self.width, self.__channels)
        img = Image.fromarray(output, 'RGB')
        img.save(filename)


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
    test()
