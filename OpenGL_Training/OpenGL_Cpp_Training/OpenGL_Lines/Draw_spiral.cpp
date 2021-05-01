/*
 *   Compile:
 *      g++ Draw_spiral.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"

int main(int argc, char **argv)
{
    Vertice center = adjust(Vertice(0, 0, 0));

    float angle = 0;
    float radius = 0;
    while (radius < min(LIMIT_X, LIMIT_Y))
    {
        vertices.push_back(center.polar(radius, angle));
        radius = angle * 0.1;
        angle = angle + 0.5;
    }

    draw(argc, argv);

    return 0;
} 
