/*
 *   Compile:
 *      g++ Draw_polygons.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Line.h"

int currentNumber = 3;
int currentRadius = 100;

void polygon(float radius, int number)
{
    vertices.clear();
    for (int i = 0; i < number; ++i)
    {
        vertices.push_back(Vertice(
            radius * cos(Radians(i * (360 / number))),
            radius * sin(Radians(i * (360 / number))),
            0 ));        
    }
    vertices.push_back(vertices[0]);
    vertices = Lines(vertices).points();
}

void move(int key_pressed)
{
    int x = 5;
    int y = 5;
    string key = "";

    switch (key_pressed)
    {
        case 101:
            x =  0;
            key = "GLUT_KEY_UP";
            break;
        case 103:
            x =  0;
            y = -y;
            key = "GLUT_KEY_DOWN";
            break;
        case 100:
            y =  0;
            x = -x;
            key = "GLUT_KEY_LEFT";
            break;
        case 102:
            y = 0;
            key = "GLUT_KEY_RIGHT";
            break;
        default:
            x = y = 0; 
    }

    if (x == 0 && y == 0)
        return;

    cout << key << ": move x(" << x << ") y(" << y << ")\n";
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i] += Vertice(x, y, 0);
}

void change(int button, int state)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        currentNumber--;
    }

    if (button == GLUT_LEFT_BUTTON)
    {
        currentNumber++;
    }

    if (currentNumber > 15) currentNumber = 15;
    if (currentNumber <  3) currentNumber =  3;

    cout << "Number: " << currentNumber << '\n';
    polygon(currentRadius, currentNumber);
}

int main(int argc, char **argv)
{
    // Set function pointer
    key_pressed = &move;
    mouse_event = &change;

    // Set polygon
    polygon(currentRadius, currentNumber);

    // OpenGL
    draw(argc, argv);

    return 0;
}
