/*
 *   Compile:
 *      g++ Draw_circles.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Circle.h"
#include "Line.h"

Circle c1(Point(50, 50), 50);

void change(int key_pressed)
{   
    static int index = 0;
    static int step = 0;

    vector<Circle> circles {
        Circle(Point( 50,  50),  30), // case 0
        Circle(Point( 50,  50), 100), // case 1
        Circle(10),                   // case 2
        Circle(40),                   // case 3
    };

    for (int angle = 0; angle < 360; angle += 15)   // case 3
    {
        Point p = c1.center().polar(c1.radius() - 15, angle);
        circles.push_back(Circle(p, 30));
    }

    for (int angle = 0; angle < 360; angle += 15)   // case 3
    {
        Point p = c1.center().polar(c1.radius() + 10, angle);
        circles.push_back(Circle(p, 30));
    }    

    int i = index % circles.size();

    figures.clear();
    if (step++ % 2 == 0)
    {
        // base
        figures.push_back(c1.points());
        figures.push_back(circles[i].points());
    }
    else
    {
        // join
        figures.push_back(Circle(c1.center(), 1).points());
        figures.push_back(Circle(circles[i].center(), 1).points());
        figures.push_back(c1.join(circles[i]));
        index++;
    }
}

int main(int argc, char **argv)
{
    // Circles
    figures.clear();
    for(int i = 0; i < 360; i += 15)
    {
      figures.push_back(Line(i / 3, i).points());
      figures.push_back(Circle(i / 3).points(0, i));
    }

    // Set function pointer
    key_pressed = &change;

    // OpenGL
    draw(argc, argv);

    return 0;
}
