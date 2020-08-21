# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
from PIL import Image
from math import sqrt


class Img(object):

    def __init__(self, height, width):

        self.width = width
        self.height = height
        self.rgbArray = np.zeros(height * width * 3, dtype='uint8')

    def isValid(self, x, y):

        if (x < 0 or x >= self.width):
            return False
        if (y < 0 or y >= self.height):
            return False

        return True

    def setPixel(self, x, y, rgb=[0, 0, 0]):

        if (not self.isValid(x, y)):
            return

        pos = 3 * (x + y * self.width)
        self.rgbArray[pos + 0] = rgb[0]  # Red
        self.rgbArray[pos + 1] = rgb[1]  # Green
        self.rgbArray[pos + 2] = rgb[2]  # Blue

    def line(self, x0, y0, x1, y1, rgb=[0, 0, 0]):

        x = x1 - x0
        y = y1 - y0
        step_x = -1 * (x < 0) + (x > 0)
        step_y = -1 * (y < 0) + (y > 0)

        d = int(sqrt(x**2 + y**2))
        for i in range(d):
            self.setPixel(x0 + (i * step_x), y0 + (i * step_y), rgb)

    def view(self):

        output = self.rgbArray.reshape(self.height, self.width, 3)
        print(output)

        display = Image.fromarray(output, 'RGB')
        display.show()


def test():

    a = Img(255, 255)
    a.line(0, 0, 254, 254, [0, 0, 255])
    a.line(127, 0, 127, 255, [255, 255, 255])
    a.line(0, 254, 254, 0, [255, 0, 0])
    a.view()


if __name__ == '__main__':
    test()
