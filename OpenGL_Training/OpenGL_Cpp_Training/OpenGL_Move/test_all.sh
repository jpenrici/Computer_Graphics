#!/bin/bash

filenames=("Draw_polygon.cpp" "Draw_polygons.cpp")

echo "Test all ..."
for item in "${filenames[@]}"; do
	echo "Compiling $item ..."
	g++ $item -o Test_Draw -lGLU -lGL -lglut -I../Tools/
	echo "Run ..."
	./Test_Draw
done
echo "Finished"

