# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

import numpy as np
import pandas as pd

h = 1  # linhas (y)
w = 2  # colunas (x)

rgb = ['R', 'G', 'B']
c = len(rgb)  # canais (z)

rgbList = np.arange(h*w*c, dtype='uint8')
rgbArray = rgbList.reshape(h, w, c)
print("rgbArray\n", rgbArray)

names = ['y', 'x', None]
index = pd.MultiIndex.from_product([range(h), range(w), rgb], names=names)
print("index\n", index)

rgbArrayFlatten = rgbArray.flatten()
print("rgbArray Flatten\n", rgbArrayFlatten)

df = pd.Series(rgbArrayFlatten, index=index)
print("pd.Series\n", df)

df = df.unstack()
print("df.unstack\n", df)

df = df.reset_index().reindex(columns=['x', 'y'] + rgb)
print("df.reindex\n", df)

print(df.describe())