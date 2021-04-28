#include "Draw.h"

int main(int argc, char **argv)
{
    vertices = adjust({
        Vertice(-1000, -1000, 0),
        Vertice( 1000, -1000, 0),
        Vertice(    0,  1000, 0),
        Vertice(-1000, -1000, 0)
    });

    draw(argc, argv);

    return 0;
}