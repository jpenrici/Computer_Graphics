/*
 *   Compile:
 *      g++ Draw_sphere_3D.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Line.h"

int main(int argc, char **argv)
{
    // Draw
    Point center(50, 50);
    float size = 10;

    figures.clear();
    for (int angleZ = 0; angleZ < 360; angleZ += 5)
    {
        for (int angleXY = 0; angleXY < 360; angleXY += 10)
        {
            Lines line({
                center.spherical(50, angleZ + size, angleXY + size),
                center.spherical(50, angleZ + size, angleXY - size),                               
            });
            figures.push_back(line.points());
        }
    }
    
    // OpenGL
    draw(argc, argv);

    return 0;
}
