# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from PIL import Image
from math import sqrt, sin, cos, radians

'''
    Conjunto de métodos e classes para estudo e manipulação de imagens.
'''


class RGB:

    __rgb = []
    __RED, __GREEN, __BLUE = 0, 1, 2

    def __init__(self, *rgb):
        '''
            in:  int,int,int
                 [int, int, int]
                 #HexHexHex
                 Int
            out: [int, int, int]
        '''
        if len(rgb) == 1 and isinstance(rgb[0], str):
            self.fromHex(rgb[0])
            return

        if len(rgb) == 1 and isinstance(rgb[0], int):
            self.fromInt(rgb[0])
            return

        if len(rgb) == 1 and isinstance(rgb[0], list) and len(rgb[0]) == 3:
            red, green, blue = rgb[0]
        elif len(rgb) == 3:
            red, green, blue = rgb[0], rgb[1], rgb[2]
        else:
            red, green, blue = 0, 0, 0

        self.__rgb = self.__config(red, green, blue)

    def __str__(self):

        text = "[{:3d}, {:3d}, {:3d}]".format(self.__rgb[0], self.__rgb[1],
                 self.__rgb[2])
        return text

    def __config(self, red, green, blue):

        # Validar tipo
        red = 0 if not isinstance(red, int) else red
        green = 0 if not isinstance(green, int) else green
        blue = 0 if not isinstance(blue, int) else blue

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

        self.__rgb = self.__config(rgb[self.__RED], rgb[self.__GREEN],
                                   rgb[self.__BLUE])

    def getRGB(self):

        return self.__rgb

    def toHex(self):
        '''
            in: [int]  rgb = [255, 255, 255]
            out: str   rgb = #FFFFFF
        '''
        text = "#"
        for i in self.__rgb:
            q = i // 16
            r = i % 16

            if q <= 9:
                text += str(q)
            else:
                text += chr(55 + q)

            if r <= 9:
                text += str(r)
            else:
                text += chr(55 + r)

        return text

    def toInt(self):
        '''
            in: [int]  rgb = [255, 255, 255]
            out: int   rgb = 16777215
        '''
        num = self.__rgb[self.__RED] * 256 * 256
        num += self.__rgb[self.__GREEN] * 256 + self.__rgb[self.__BLUE]

        return num

    def fromInt(self, num):
        '''
            in: int     rgb = 16777215
            out: [int]  rgb = [255, 255, 255]
        '''
        red = num // (256 * 256)
        num %= 256 * 256
        green = num // 256
        num %= 256
        blue = num

        self.setRGB(red, green, blue)

    def __hex2int(self, text):

        num = 0
        text = text[::-1].upper()
        for i in range(len(text)):
            value = ord(text[i])
            if value >= ord('0') and value <= ord('9'):
                value = value - ord('0')
            if value >= ord('A') and value <= ord('F'):
                value = value - ord('A') + 10
            num += value * 16 ** i

        return num

    def fromHex(self, text):
        '''
            in: str     rgb = #FFFFFF
            out: [int]  rgb = [255, 255, 255]
        '''
        if text == "" or len(text) != 7:
            print("failed to execute")
            return

        text = text.replace('#', "")
        red = self.__hex2int(text[0:2])
        green = self.__hex2int(text[2:4])
        blue = self.__hex2int(text[4:6])

        self.setRGB(red, green, blue)


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


if __name__ == '__main__':
    pass
