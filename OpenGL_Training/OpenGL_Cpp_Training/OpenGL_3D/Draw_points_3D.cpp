/*
 *   Compile:
 *      g++ Draw_points_3D.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Circle.h"

int main(int argc, char **argv)
{
    // Draw
    Point center(50, 50);
    vertices.clear();
    for (int angleZ = 0; angleZ < 360; angleZ += 15)
    {
        for (int angleXY = 0; angleXY < 360; angleXY += 15)
        {
            Point p = center.spherical(50, angleZ, angleXY);
            vertices.push_back(p);
        }
    }
    
    // OpenGL
    draw(argc, argv);

    return 0;
}
