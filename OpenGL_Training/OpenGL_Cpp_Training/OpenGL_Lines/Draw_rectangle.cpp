/*
 *   Compile:
 *      g++ Draw_rectangle.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Rectangle.h"

Rectangle r1(Point(50, 50), 100, 100);

void change(int key_pressed)
{   
    static int index = 0;

    vector<Rectangle> rectangles {    
        Rectangle(Point( 55,  55), 50, 50), // case 0
        Rectangle(Point( 75, 145), 50, 50), // case 1
        Rectangle(Point( 75,  10), 50, 50), // case 2
        Rectangle(Point(125,  75), 50, 50), // case 3
        Rectangle(Point( 10,  75), 50, 50), // case 4
        Rectangle(Point( 10,  15), 50, 50), // case 5
        Rectangle(Point( 10, 135), 50, 50), // case 6
        Rectangle(Point(125, 135), 50, 50), // case 7
        Rectangle(Point(125,  15), 50, 50), // case 8
    };

    int i = index++ % rectangles.size();
    cout << "case " << i << '\n';

    vertices = r1.join(rectangles[i]);
}

int main(int argc, char **argv)
{
    // Rectangle
    vertices = r1.polygon();
    vertices.push_back(vertices.front());

    // Set function pointer
    key_pressed = &change;

    // OpenGL
    draw(argc, argv);  

    return 0;
}
