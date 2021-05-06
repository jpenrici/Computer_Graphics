/*
 *   Compile:
 *      g++ Draw_rose.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"

int main(int argc, char **argv)
{
    Vertice center = Vertice(0, 0);

    int num = 7;
    float radius = 0;
    float length = 100;
    for (int angle = 0; angle < 360; angle++)
    {
        radius = length * cos (num * (angle * PI) / 180.00);
        vertices.push_back(center.polar(radius, angle));
        // length += 0.1;
    }

    draw(argc, argv);

    return 0;
} 