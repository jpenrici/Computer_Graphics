#!/bin/bash

filenames=("Draw_circles_3D.cpp" "Draw_lines_3D.cpp" "Draw_points_3D.cpp" \
	"Draw_sphere_3D.cpp")

echo "Test all ..."
for item in "${filenames[@]}"; do
	echo "Compiling $item ..."
	g++ $item -o Test_Draw -lGLU -lGL -lglut -I../Tools/
	echo "Run ..."
	./Test_Draw
done
echo "Finished"
