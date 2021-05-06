/*
 *   Compile:
 *      g++ Draw_triangle.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"

int main(int argc, char **argv)
{
    vertices = {
        Vertice(-100, -100, 0),
        Vertice( 100, -100, 0),
        Vertice(   0,  100, 0),
        Vertice(-100, -100, 0)
    };

    draw(argc, argv);

    return 0;
}
