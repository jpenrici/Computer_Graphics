# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from PIL import Image
from math import sqrt, sin, cos


class RGB:

    __rgb = []

    def __init__(self, red=255, green=255, blue=255):

        self.__rgb = self.__config(red, green, blue)

    def __config(self, red, green, blue):

        # Limites
        red = 0 if red < 0 else red
        green = 0 if green < 0 else green
        blue = 0 if blue < 0 else blue

        red = 255 if red > 255 else red
        green = 255 if green > 255 else green
        blue = 255 if blue > 255 else blue

        return [red, green, blue]

    def setRGB(self, red, green, blue):

        self.__rgb = self.__config(red, green, blue)

    def setColor(self, rgb=None):

        if rgb is None:
            return
        if len(rgb) != 3:
            return

        self.__rgb = self.__config(rgb[0], rgb[1], rgb[2])

    def getRGB(self):

        return self.__rgb


class Color:

    RED = [255, 0, 0]
    GREEN = [0, 255, 0]
    BLUE = [0, 0, 255]
    BLACK = [0, 0, 0]
    WHITE = [255, 255, 255]


class Img:

    def __init__(self, height, width):

        self.width = width
        self.height = height
        self.rgbArray = np.zeros(height * width * 3, dtype='uint8')

    def __isValid(self, x, y):

        if (x < 0 or x >= self.width):
            return False
        if (y < 0 or y >= self.height):
            return False

        return True

    def setPixel(self, x, y, rgb=Color.WHITE):

        if (not self.__isValid(x, y)):
            return

        pos = 3 * (x + y * self.width)
        self.rgbArray[pos + 0] = rgb[0]  # Red
        self.rgbArray[pos + 1] = rgb[1]  # Green
        self.rgbArray[pos + 2] = rgb[2]  # Blue

    def line(self, x0, y0, x1, y1, rgb=Color.WHITE):

        x = x1 - x0
        y = y1 - y0
        step_x = -1 * (x < 0) + (x > 0)
        step_y = -1 * (y < 0) + (y > 0)

        d = int(sqrt(x**2 + y**2))
        for i in range(d):
            self.setPixel(x0 + (i * step_x), y0 + (i * step_y), rgb)

    def circle(self, x0, y0, radius=2, start=0, stop=360, rgb=Color.WHITE):
        pass

    def rectangle(self, x0, y0, height=2, width=2, rgb=Color.WHITE):
        pass

    def view(self):

        output = self.rgbArray.reshape(self.height, self.width, 3)
        print(output)

        display = Image.fromarray(output, 'RGB')
        display.show()


def test():

    # RGB
    c1 = RGB()
    print(c1.getRGB())  # esperado [255, 255, 255]
    c1.setRGB(-1, 0, 300)
    print(c1.getRGB())  # esperado [0, 0, 255]
    c1.setColor(Color.RED)
    print(c1.getRGB())  # esperado [255, 0, 0]

    # Desenhos
    a = Img(255, 255)
    a.line(0, 0, 254, 254)  # branca
    a.line(127, 0, 127, 254, Color.BLUE)
    a.line(0, 254, 254, 0, Color.GREEN)
    a.line(0, 50, 254, 50, [127, 127, 127])
    a.line(50, 127, 200, 127, c1.getRGB())
    a.view()


if __name__ == '__main__':
    test()
