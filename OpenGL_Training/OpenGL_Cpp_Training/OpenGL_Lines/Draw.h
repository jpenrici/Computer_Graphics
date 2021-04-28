#include "Geometry.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <vector>

using namespace std;

#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 500
#define LIMIT_X       SCREEN_WIDTH  * 0.45
#define LIMIT_Y       SCREEN_HEIGHT * 0.45
#define ORIGIN_X      SCREEN_WIDTH  * 0.50
#define ORIGIN_Y      SCREEN_HEIGHT * 0.50

typedef Vector3D         Vertice;
typedef vector<Vector3D> Vertices;

Vertices vertices;
const Vertice ORIGIN(ORIGIN_X, ORIGIN_Y, 0);

void init();
void display(void);
void keyboard(unsigned char key, int x, int y);
Vertice adjust(Vertice vertice);
Vertices adjust(Vertices vertices);

int draw(int argc, char** argv)
{
    // OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL : Press ESC to exit");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Y axis
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(ORIGIN_X, 0.0, 0.0);
        glVertex3f(ORIGIN_X, SCREEN_HEIGHT, 0.0);
    glEnd();

    // X axis
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, ORIGIN_Y, 0.0);
        glVertex3f(SCREEN_WIDTH, ORIGIN_Y, 0.0);
    glEnd();

    // Draw
    if (!vertices.empty())
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
            for (auto v : vertices)
                glVertex3f(v.getX(), v.getY(), v.getZ());
        glEnd();
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Esc
            exit(0);
            break;
    }
}

Vertice adjust(Vertice vertice)
{
    vertice.normalize();
    vertice *= Vertice(LIMIT_X, LIMIT_Y, 0);
    
    return Vertice(ORIGIN_X + vertice.getX(), ORIGIN_Y - vertice.getY(), 0);
}

Vertices adjust(Vertices vertices)
{
    Vertices temp;
    for (auto v : vertices)
        temp.push_back(adjust(v));
    
    return temp;
}
