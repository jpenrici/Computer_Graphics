/*
 *   Compile:
 *      g++ Draw_triangle.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/

#include "Draw.h"
#include "Triangle.h"

int main(int argc, char **argv)
{
    vertices = Triangle(Vertice(-50, 0), 100, 100).poligon();

    draw(argc, argv);

    return 0;
}
