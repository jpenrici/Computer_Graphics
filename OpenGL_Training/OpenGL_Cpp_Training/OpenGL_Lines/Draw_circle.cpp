/*
 *   Compile:
 *      g++ Draw_circle.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Circle.h"

Circle c1(Point(50, 50), 100);

void change(int key_pressed)
{   
    static int index = 0;

    vector<Circle> circles {    
        Circle(Point( 50,  50),   5),
        Circle(Point( 50,  50),  15),
        Circle(Point( 50,  50),  50),
        Circle(Point( 50,  50), 100),
        Circle(Point(-50, -50),   5),
        Circle(Point(-50, -50),  15),
        Circle(Point(-50, -50),  50),
        Circle(Point(-50, -50), 100)
    };

    int i = index++ % circles.size();
    vertices = circles[i].points();   
}

int main(int argc, char **argv)
{
    // Circles
    vertices = c1.points();

    // Set function pointer
    key_pressed = &change;

    // OpenGL
    draw(argc, argv);  

    return 0;
}
