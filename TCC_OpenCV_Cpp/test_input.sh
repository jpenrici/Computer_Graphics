#!/bin/bash

echo "compile and execute..."
g++ -std=c++17 image_processing.cpp -o image_processing

# test [argc, argv]
echo "test 1 ..."
./image_processing 1 2 3 						; echo		# usage ...
./image_processing 1 2 							; echo		# ignore
./image_processing 1 							; echo		# ignore
./image_processing 								; echo		# is empty
./image_processing -png 						; echo		# ignore
./image_processing --PNG 						; echo		# is empty
./image_processing --JPG 						; echo		# is empty
./image_processing --JPEG 						; echo		# is empty
./image_processing /directory/images/ 			; echo		# ignore
./image_processing --JPEG /directory/images/ 	; echo		# ignore

echo "test 2 ..."
./image_processing 								; echo		# is empty
./image_processing images 						; echo		# list
./image_processing --PNG images 				; echo		# list
./image_processing --JPG images 				; echo		# list
./image_processing --JPEG images 				; echo		# list
