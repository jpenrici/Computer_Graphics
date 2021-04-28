#include "Draw.h"

int main(int argc, char **argv)
{
    Vertice center = adjust(Vertice(0, 0, 0));

    int number = 24;
    float radius_1 = 200;
    float radius_2 = 50;
    
    for (int i = 0; i < number; ++i)
    {
        if (i % 2 == 0)
            vertices.push_back(center.polar(radius_1, i * 360 / number));
        else
            vertices.push_back(center.polar(radius_2, i * 360 / number));
    }
    vertices.push_back(vertices[0]);

    draw(argc, argv);

    return 0;
} 