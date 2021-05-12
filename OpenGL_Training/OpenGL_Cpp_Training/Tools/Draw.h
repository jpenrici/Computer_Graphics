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
#define WPOSX         300.0
#define WPOSY         100.0
#define DEPTH         SCREEN_WIDTH
#define ORIGIN_X      SCREEN_WIDTH  * 0.50
#define ORIGIN_Y      SCREEN_HEIGHT * 0.50
#define ORIGIN_Z      DEPTH * 0.5

typedef Vector3D         Vertice;
typedef vector<Vector3D> Vertices;

/* GLOBAL */
Vertices vertices;
vector <Vertices> figures;
GLfloat angle, fAspect;
GLfloat eyeX, eyeY, eyeZ;
GLfloat upX, upY, upZ;

/* CONSTANT */
const Vertice ORIGIN(ORIGIN_X, ORIGIN_Y, ORIGIN_Z);

/* FUNCTIONS */
void init(void);
void display(void);
void view(void);
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

int draw(int argc, char** argv)
{
    // OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(WPOSX, WPOSY);
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
    angle = 90;
    eyeX = ORIGIN_X;
    eyeY = ORIGIN_Y;
    eyeZ = 0;
    upX = 0;
    upY = 1;
    upZ = 0;    

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Z axis
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(ORIGIN_X, ORIGIN_Y, 0.0);
        glVertex3f(ORIGIN_X, ORIGIN_Y, DEPTH);
    glEnd();

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

void view(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluPerspective(fovy, aspect, zNear, zFar)
    gluPerspective(angle, fAspect, 0.1, DEPTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (eyeX < 0) eyeX = 0;
    if (eyeY < 0) eyeY = 0;
    if (eyeZ < 0) eyeZ = 0;    

    if (eyeX > SCREEN_WIDTH) eyeX = SCREEN_WIDTH;
    if (eyeY > SCREEN_HEIGHT) eyeY = SCREEN_HEIGHT;
    if (eyeZ > DEPTH) eyeZ = DEPTH;    

    gluLookAt(eyeX, eyeY, eyeZ, ORIGIN_X, ORIGIN_Y, ORIGIN_Z, upX, upY, upZ);
}

void reshape(int width, int height)
{
    if (height == 0) height = 1;
    fAspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    view();
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
        case 'x':
            eyeX++;
            break;
        case 'X':
            eyeX--;
            break;
        case 'y':
            eyeY++;
            break;
        case 'Y':
            eyeY--;
            break;
        case 'z':
            eyeZ++;
            break;
        case 'Z':
            eyeZ--;
            break;
        case 'o':
        case 'O':
            init();
            break;
    }

    view();
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
            float x = ORIGIN_X - v.getX();
            float y = ORIGIN_Y + v.getY();
            float z = ORIGIN_Z + v.getZ();

            if (x < 0) x = 0;
            if (x > SCREEN_WIDTH) x = SCREEN_WIDTH;

            if (y < 0) y = 0;
            if (y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;

            if (z < 0) z = 0;
            if (z > DEPTH) z = DEPTH;
            
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

#endif // __Draw_H__
