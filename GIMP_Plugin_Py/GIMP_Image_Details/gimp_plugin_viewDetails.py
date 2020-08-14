# -*- Mode: Python2; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

'''
    View Details
    =========

    Example to view image details.
    Use Numpy, Pandas.

    pdb.python_fu_viewDetails(img, drw ...)
'''

# Py 2.7
import os
import sys
import datetime
from array import array

# Constantes e símbolos gimp, pdb, register e a função main
from gimpfu import *

# Descrição
LABEL = "View Details"
INFO = "Use advanced libraries to detail the image."
HELP = globals()["__doc__"]

# Local
HOME = os.environ['HOME']
FULL_PATH = os.path.realpath(__file__)
PATH, FILENAME = os.path.split(FULL_PATH)
ENV = PATH + "/pyenv/lib/python2.7"

# Log
now = datetime.datetime.now()
log = "\nGIMP: " + str(now.strftime("%Y-%m-%d %H:%M:%S"))
log += "\nPlug-in: " + LABEL + '\n'
logError = "Unexpected error: "

# Virtualenv
if not os.path.isdir(ENV):
    logError += "pyenv/lib/python2.7 ... not found\n"
else:
    sys.path.extend([ENV, ENV + "/site-packages",
                     ENV + "/site-packages/setuptools"])

# Dependências
dependencies = True
try:
    import numpy as np
    log += "numpy " + np.__version__ + " ... ok\n"
except ImportError as err:
    logError += str(err) + " not found\n"
    dependencies = False
try:
    import pandas
    log += "pandas " + np.__version__ + " ... ok\n"
except ImportError as err:
    logError += str(err) + " not found\n"
    dependencies = False

if (not dependencies):
    log += logError
#print(log)


def message(msg):
    pdb.gimp_message(msg)


def pxRgnToArray(layer):
    rgn = layer.get_pixel_rgn(0, 0, layer.width, layer.height, False, False)
    values = array("B", rgn[0:layer.width, 0:layer.height])  # uchar -> int
    return values  # vetor


def pxRgnToNumpy(layer):
    values = pxRgnToArray(layer)
    npArray = np.array(values, dtype=np.uint8)
    return npArray.reshape(layer.height, layer.width, layer.bpp)  # matriz


def pxRgnToTxt(layer):
    # função lenta para matriz com muitos pixels
    text = ""
    values = pxRgnToArray(layer)

    i = 1
    j = 1
    for v in values:
        text += str(v)
        if (i < layer.bpp):
            text += ','
            i += 1
        else:
            i = 1
            if (j < (layer.width)):
                text += ';'
                j += 1
            else:
                pdb.gimp_progress_pulse()
                text += '\n'
                j = 1

    return text


def exportTxt(filename, text):
    try:
        filename = open(filename, "w")
        filename.write(text)
        filename.close()
    except Exception:
        pass


def saveLog(text):
    filename = "LogGimpPlugin_" + str(now.strftime("%Y%m%d_%H%M%S")) + ".txt"
    exportTxt(filename, text)


def viewDetails(img, layer, directory, export):

    global log

    # Checar dependências
    if (not dependencies):
        message(LABEL + ", error: missing dependencies ...")
        saveLog(log)
        return

    inform = "Processing " + img.name + " ..."
    gimp.progress_init(inform)

    log += inform + '\n'
    filename = directory + "/" + (layer.name).replace('.', '_')  # export

    try:
        img_copy = pxRgnToNumpy(layer)
        log += layer.name + " to npArray ...\n"

        if (export):
            start = datetime.datetime.now()
            log += "local: " + directory + " ...\n"
            log += layer.name + " export data ...\n"

            # salvar matriz de pixels em dados Numpy
            pdb.gimp_progress_set_text("saving Numpy file ...")
            np.save(filename, img_copy)

            # salvar matriz de pixels em Txt
            pdb.gimp_progress_set_text("converting matrix to text, please wait ...")
            exportTxt(filename + ".txt", pxRgnToTxt(layer))
            pdb.gimp_progress_set_text("saving TXT file ...")

            end = datetime.datetime.now()
            log += "time: " + str((end - start).seconds) + " seconds ...\n"

    except Exception as err:
        log += "[Error - Gimp Plugin: " + FILENAME + "]: " + str(err) + '\n'
        gimp.message(LABEL + " failed.")

    pdb.gimp_progress_end()

    print(log)      # Log no console Linux


gettext.install("gimp20-python", gimp.locale_directory, unicode=True)

# Registro do plug-in
register(
    "viewDetails",         # nome da função
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
        (PF_DIRNAME, "directory", _("Directory"), HOME),
        (PF_BOOL, "export", _("Export Matrix Data"), False)
    ],
    [], # parâmetros de saída do método
    viewDetails,           # nome de chamada do método
    menu="<Image>/Image",  # caminho no menu
    domain=("gimp20-python", gimp.locale_directory)
    # on_query=None,
    # on_run=None
)

# Função princiapl, chamada após o registro do plug-in
main()
