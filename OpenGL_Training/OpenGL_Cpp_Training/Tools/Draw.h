#ifndef __Draw_H__
#define __Draw_H__

#include "Geometry.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define SCREEN_WIDTH  500.0
#define SCREEN_HEIGHT 500.0
#define ORIGIN_X      SCREEN_WIDTH  * 0.50
#define ORIGIN_Y      SCREEN_HEIGHT * 0.50
#define ORIGIN_Z      0.0

typedef Vector3D         Vertice;
typedef vector<Vector3D> Vertices;

Vertices vertices;
vector <Vertices> figures; 
const Vertice ORIGIN(ORIGIN_X, ORIGIN_Y, ORIGIN_Z);

void init(void);
void display(void);
void reshape(int width, int height);
void idle(void);

void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouseEvent(int button, int state, int x, int y);
void (*key_pressed)(int key);               // Function Pointer - KeyboardFunc
void (*mouse_event)(int button, int state); // Function Pointer - MouseFunc

void make(Vertices vertices);
bool load(string filename);
bool save(string filename);

/* FUNCTIONS */

int draw(int argc, char** argv)
{
    // OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL : Press ESC to exit");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseEvent);  
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

void init(void)
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
        glVertex3f(ORIGIN_X, 0.0, ORIGIN_Z);
        glVertex3f(ORIGIN_X, SCREEN_HEIGHT, ORIGIN_Z);
    glEnd();

    // X axis
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, ORIGIN_Y, ORIGIN_Z);
        glVertex3f(SCREEN_WIDTH, ORIGIN_Y, ORIGIN_Z);
    glEnd();

    // Draw
    if (!figures.empty())
    {
        for (auto figure : figures)
            make(figure);
    }
    else
    {
        make(vertices);
    }

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void idle(void)
{
    glutPostRedisplay();
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

void specialKeys(int key, int x, int y)
{
    if (key_pressed != NULL)
        key_pressed(key);
    else
        cout << "special keys : No action. Nothing to do.\n";
}

void mouseEvent(int button, int state, int x, int y)
{
    if (mouse_event != NULL)
        mouse_event(button, state);
    else
        cout << "mouse : No action. Nothing to do.\n";    
}

bool load(string filename)
{
    ifstream fileIn(filename, ios::in | ios::binary);
    
    if(!fileIn)
    { 
        cerr << "I/O error.\n";
        return false;
    }

    float x, y, z;
    vertices.clear();

    fileIn.seekg(0);
    while (fileIn && !fileIn.eof())
    {   
        fileIn.read((char *)(&x), sizeof(float));
        fileIn.read((char *)(&y), sizeof(float));
        fileIn.read((char *)(&z), sizeof(float));        
        if (!fileIn.eof())
            vertices.push_back(Vertice(x, y, z));
    }

    fileIn.clear();
    fileIn.close(); 

    return true;
}

bool save(string filename)
{
    if (vertices.empty())
    {
        cout << "Vertices list empty. Nothing to do.\n";
        return false;
    }

    string extension = "";
    if (filename.size() > 4)
        extension = filename.substr(filename.size() - 4, 4);

    if (extension == ".txt")
    {
        ofstream fileOut(filename);

        if(!fileOut)
        { 
            cerr << "I/O error.\n";
            return false;
        }       

        for (auto vertice: vertices)
            fileOut << vertice.csv() << '\n';

        fileOut.clear();
        fileOut.close();

        return true;        
    }

    if (extension == ".dat")
    {
        ofstream fileOut(filename, ios::out | ios::binary);

        if(!fileOut)
        { 
            cerr << "I/O error.\n";
            return false;
        }

        float value;
        fileOut.seekp(0);
        for (auto vertice : vertices)
        {
            value = vertice.getX();
            fileOut.write((const char *)(&value), sizeof(float));

            value = vertice.getY();
            fileOut.write((const char *)(&value), sizeof(float));            
           
            value = vertice.getZ();
            fileOut.write((const char *)(&value), sizeof(float));
        }

        fileOut.clear();
        fileOut.close();

        return true;
    }

    return false;
}

void make(Vertices vertices)
{
    if (!vertices.empty())
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        for (auto v : vertices)
        {
            float x = ORIGIN_X + v.getX();
            float y = ORIGIN_Y - v.getY();

            if (x < 0) x = 0;
            if (x > SCREEN_WIDTH) x = SCREEN_WIDTH;

            if (y < 0) y = 0;
            if (y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;
            
            glVertex3f(x, y, v.getZ());
        }
        glEnd();
    }
}

#endif // __Draw_H__
