/*
 *   Compile:
 *      g++ Draw_lines.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Line.h"

int main(int argc, char **argv)
{
    vertices = {
        Vertice(-50, -50, 0),
        Vertice( 50, -50, 0),
        Vertice(  0,  50, 0),
        Vertice( 25,  25, 0),
        Vertice(  0,   0, 0)
    };

    string name = "Draw_lines_vertices";

    save(name + ".txt");
    save(name + ".dat");

    load(name + ".dat");

    figures.clear();
    for (int i = 0; i < vertices.size() - 1; ++i)
        figures.push_back(Lines(vertices).points());
    
    draw(argc, argv);    

    return 0;
}
