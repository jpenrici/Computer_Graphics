/*
 *   Compile:
 *      g++ Draw_circles_3D.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Circle.h"

int main(int argc, char **argv)
{
	// Draw
    figures.clear();
    for (int i = -50; i < 50; i += 2)
    {
        figures.push_back(Circle(Point(50, 50, i), 100 - i).points(0, 360, 0.1));
    }
    
    // OpenGL
    draw(argc, argv);

    return 0;
}
