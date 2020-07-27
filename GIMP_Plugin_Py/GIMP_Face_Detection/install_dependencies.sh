#!/bin/bash
# Checar dependências Python para uso no GIMP Plugin.

separator="--------------------------------------------------------------------"
pyVersion=$(python -c 'import sys; print(".".join(map(str, sys.version_info[:2])))')

echo $separator
echo "Python: $pyVersion"

if [ $pyVersion != "2.7" ]; then
	echo "Install Python 2.7"
	exit
fi

echo "Creating virtualenv ..."
if [ ! -d "pyenv" ]; then

	echo "Installing pyenv ..."
	
	python2.7 -m pip install --user virtualenv
	python2.7 -m virtualenv pyenv
	source pyenv/bin/activate
	python2.7 -m pip install numpy
	python2.7 -m pip install opencv-python
# 	python2.7 -m pip install scikit-image
	deactivate

	echo ""
	echo "Finished."

else
	echo "Environment already setup!"
fi

echo $separator
echo ""