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
    circle(circles[i].center(), circles[i].radius(), 0, 360);
}

int main(int argc, char **argv)
{
    // Set function pointer
    key_pressed = &change;

    // OpenGL
    draw(argc, argv);  

    return 0;
}
