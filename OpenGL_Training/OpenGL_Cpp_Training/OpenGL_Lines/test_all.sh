#!/bin/bash

filenames=(
	"Draw_circle.cpp" "Draw_circles.cpp" "Draw_lines.cpp" "Draw_rectangle.cpp" \
	"Draw_rose.cpp" "Draw_spiral.cpp" "Draw_star.cpp" "Draw_triangle.cpp")

echo "Test all ..."
for item in "${filenames[@]}"; do
	echo "Compiling $item ..."
	g++ $item -o Test_Draw -lGLU -lGL -lglut -I../Tools/
	echo "Run ..."
	./Test_Draw
done
echo "Finished"
