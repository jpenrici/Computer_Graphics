# -*- Mode: Python; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

'''
    Face Detection with OpenCV
    ==============
    Opencv-python and Numpy requirements.
'''

# Py 2.7
import os
import sys
import datetime
from array import array

# Constantes e símbolos gimp, pdb, register e a função main
from gimpfu import *

# Descrição
LABEL = "Face Detection"
INFO = "Detect face in image."
HELP = globals()["__doc__"]

# Local
FULL_PATH = os.path.realpath(__file__)
PATH, FILENAME = os.path.split(FULL_PATH)

ENV = PATH + "/pyenv/lib/python2.7"
CASCADE_PATH = PATH + "/haarcascade_frontalface_default.xml"

# Log
log = "\nGIMP: " + str(datetime.datetime.now().strftime("%b %d %Y %H:%M:%S"))
log += "\nPlug-in: " + LABEL + '\n'
logError = "Unexpected error: "

# Virtualenv
if not os.path.isdir(ENV):
    logError += "pyenv/lib/python2.7 ... not found\n"
else:
    sys.path.extend([ENV, ENV + "/site-packages", ENV + "/site-packages/setuptools"])

# Dependências
dependencies = True
try:
    import numpy as np
    log += "numpy " + np.__version__ + " ... ok\n"
except ImportError as err:
    logError += err + " not found\n"
    dependencies = False
try:
    import cv2 as cv
    log += "opencv " + cv.__version__ + " ... ok\n"
except ImportError as err:
    logError += err + " not found\n"
    dependencies = False

if not os.path.isfile(CASCADE_PATH):
    logError += CASCADE_PATH + " not found\n"
    dependencies = False
else:
    log += CASCADE_PATH + " ... ok\n"

log += logError


def message(msg):
    pdb.gimp_message(msg)


def pxRgnToNumpy(layer):
    rgn = layer.get_pixel_rgn(0, 0, layer.width, layer.height, False, False)
    values = array("B", rgn[0:layer.width, 0:layer.height])  # uchar -> int
    return np.array(values, dtype=np.uint8).reshape(layer.height, layer.width,
                   layer.bpp)


def createNewLayer(img, name, npArray):
    newLayer = gimp.Layer(img, name, img.width, img.height, img.active_layer.type,
                    100, NORMAL_MODE)
    rgn = newLayer.get_pixel_rgn(0, 0, newLayer.width, newLayer.height, True)
    rgn[:, :] = np.uint8(npArray).tobytes()  # gimp.PixelRgn
    img.add_layer(newLayer, lastLayer(img))
    gimp.displays_flush()


def lastLayer(img):
    pos = 0
    for i in range(len(img.layers)):
        if(img.layers[i] == img):
            pos = i
    return pos


def saveLog(text):
    filename = "LogGimpPlugin.txt"
    try:
        filename = open(filename, "w")
        filename.write(text)
        filename.close()
    except Exception:
        pass


def faceDetection(img, layer):

    global log

    # Checar dependências
    if (not dependencies):
        message(LABEL + ", error: missing dependencies ...")
        saveLog(log)
        return

    inform = "Processing " + img.name + " ..."
    log += inform + '\n'
    gimp.progress_init(inform)
    pdb.gimp_image_undo_group_start(img)

    try:
        # OpenCV
        img_copy = pxRgnToNumpy(layer)
        img_gray = cv.cvtColor(img_copy, cv.COLOR_BGR2GRAY)
        log += layer.name + " to npArray ...\n"

        clf = cv.CascadeClassifier(CASCADE_PATH)
        faces = clf.detectMultiScale(img_gray, 1.3, 5)

        hits = 0
        for (x, y, w, h) in faces:
            hits += 1
            img_copy = cv.rectangle(img_copy, (x, y), (x+w, y+h), (0, 0, 0), 2)

        log += str(hits) + " faces detected ...\n"
        if hits > 0:
            name = layer.name + " faces"
            createNewLayer(img, name, img_copy)
            log += img.name + " create layer " + name + " ...\n"
            # cv.imwrite("temp_" + layer.name, img_copy)
        else:
            message("detection not possible.")

        pdb.gimp_selection_none(img)
        pdb.gimp_image_undo_group_end(img)

        gimp.displays_flush()

        log += inform + " ok\n"

    except Exception as err:
        log += "[Gimp Plugin: " + FILENAME + "]: " + str(err) + '\n'
        gimp.message(LABEL + " failed.")

    pdb.gimp_progress_end()

    print(log)      # Log no console Linux
    saveLog(log)    # Opcional


gettext.install("gimp20-python", gimp.locale_directory, unicode=True)

# Registro do plug-in
register(
    "faceDetection",       # nome da função
    N_(INFO),              # sobre o plug-in
    HELP,                  # docstring como Help
    "jpenrici",            # autor
    "GPL V2 License",      # licença
    "2020",                # data de criação (ano)
    N_(LABEL),             # rótulo do plugin no menu
    "RGB*",                # tipos de imagens suportados
    [   # parâmetros de entrada do método
        (PF_IMAGE, "img", _("_Image"), None),
        (PF_DRAWABLE, "drw", _("_Drawable"), None),
    ],
    [], # parâmetros de saída do método
    faceDetection,         # nome de chamada do método
    menu="<Image>/Image",  # caminho no menu
    domain=("gimp20-python", gimp.locale_directory)
    # on_query=None,
    # on_run=None
)

# Função princiapl, chamada após o registro do plug-in
main()
