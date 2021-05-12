/*
 *   Compile:
 *      g++ Draw_lines_3D.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Line.h"

int main(int argc, char **argv)
{
    vertices = {
        Vertice(  0,   0,  0),
        Vertice( 50,   0,  0),
        Vertice( 25,  50,  0),
        Vertice(  0,  25,  0),
        Vertice(  0,  25,-10),
        Vertice( 50,   0,-10),
        Vertice( 25,  50,-10),
        Vertice(  0,  25,-10),
        Vertice(  0,   0,  0)

    };

    // Draw
    figures.clear();
    for (int i = 0; i < vertices.size() - 1; ++i)
        figures.push_back(Lines(vertices).points());
    
    // OpenGL
    draw(argc, argv);

    return 0;
}
