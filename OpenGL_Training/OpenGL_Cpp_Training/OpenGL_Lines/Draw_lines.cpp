/*
 *   Compile:
 *      g++ Draw_lines.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"

int main(int argc, char **argv)
{
    vertices = adjust({
        Vertice(-5000, -5000, 0),
        Vertice( 5000, -5000, 0),
        Vertice(    0,  5000, 0),
        Vertice( 2500,  2500, 0),
        Vertice(    0,     0, 0)
    });

    string name = "Draw_lines_vertices";

    save(name + ".txt");
    save(name + ".dat");

    load(name + ".dat");
    draw(argc, argv);    

    return 0;
}
