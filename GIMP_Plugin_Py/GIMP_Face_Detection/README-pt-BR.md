Gimp_Face_Detection
===================

Neste plug-in é experimentado a potencialidade do OpenCV e do GIMP Plugin para marcação de faces na imagem usando o recurso Haar Cascades.

Instalação
==========
[1] Instale OpenCV e NumPy para a versão Python 2.7, conforme indicação dos sites oficiais. 
[2] Seguir os passos da instalação padrão de um GIMP Plugin.
[3] Copie os arquivos `gimp_plugin_faceDetection.py`, `haarcascade_frontalface_default.xml` e `install_dependencies.sh` para o diretório `plug-ins`.
[4] No Linux, se necessário, instale o `virtualenv`. Dê permissão ao arquivo `install_dependencies.sh` e execute o código.
[5] Siga os passos finais da instalação GIMP Plugin padrão.

Requerimentos
=============

	- [OpenCV] (https://opencv.org/)
	- [NumPy](https://numpy.org/)
	- [Virtualenv](https://pypi.org/project/virtualenv/) (Opcional)

Referências
===========

[OpenCV](https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_objdetect/py_face_detection/py_face_detection.html) Detecção de Faces usando Haar Cascades.
[GIMP Developer](https://developer.gimp.org/plug-ins.html) Tutorial GIMP Plugin.
[Paul Bourke](http://paulbourke.net/) Algoritmos de Computação Gráfica.
[Akkana e Joao](https://shallowsky.com/blog/gimp/pygimp-pixel-ops.html) Algoritmo de operações de pixel no GIMP.
[Kritik Soman](https://arxiv.org/abs/2004.13060) Inspiração no uso de GIMP Python Plugins em Visão Computacional.