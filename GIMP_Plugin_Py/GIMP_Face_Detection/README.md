Gimp_Face_Detection
===================

In this plug-in, the potential of OpenCV and the GIMP Plugin to experience faces in the image using the Haar Cascades feature is experienced.

[README-pt-BR](https://github.com/jpenrici/Computer_Graphics/blob/master/GIMP_Plugin_Py/GIMP_Face_Detection/README-pt-BR.md)

Installation Steps
===================

[1] Install OpenCV and NumPy for Python version 2.7, as indicated by the official websites. <br>
[2] Follow the steps for the standard installation of a GIMP Plugin. <br>
[3] Copy the files `gimp_plugin_faceDetection.py`,` haarcascade_frontalface_default.xml` and `install_dependencies.sh` to the` plug-ins` directory. <br>
[4] On Linux, if necessary, install `virtualenv`. Give the `install_dependencies.sh` file permission and run the code. <br>
[5] Follow the final steps of the standard GIMP Plugin installation. <br>

Requeriments
============

[OpenCV](https://opencv.org/)
[NumPy](https://numpy.org/)
[Virtualenv](https://pypi.org/project/virtualenv/) (Opcional)

References
==========

[OpenCV](https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_objdetect/py_face_detection/py_face_detection.html) Detecção de Faces usando Haar Cascades.
[GIMP Developer](https://developer.gimp.org/plug-ins.html) Tutorial GIMP Plugin.
[Paul Bourke](http://paulbourke.net/) Algoritmos de Computação Gráfica.
[Akkana e Joao](https://shallowsky.com/blog/gimp/pygimp-pixel-ops.html) Algoritmo de operações de pixel no GIMP.
[Kritik Soman](https://arxiv.org/abs/2004.13060) Inspiração no uso de GIMP Python Plugins em Visão Computacional.