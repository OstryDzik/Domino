
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#include "Scene.h"
#include "DominoSet.h"
#include "Camera.h"
#include "Table.h"

static bool g_bButtonLDown = false;
static bool g_bButtonRDown = false;

static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1500;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static int g_xClick = 0;
static float g_lightPos[4] = { 0, 100, 0, 1 };  // Position of light

static double tableSizeX = 300;
static double tableSizeZ = 500;
static double tableSizeY = 100;
static double tableThickness = 10;
static double roomSizeX = 1200;
static double roomSizeY = 1200;
static double roomSizeZ = 1200;

Camera* camera = new Camera(0, 0, -tableSizeZ, 90, 45, -tableSizeY, roomSizeX, roomSizeX);
DominoSet* dominoSet = new DominoSet(50);
Table* table = new Table(-tableSizeX / 2, -tableSizeY, -tableSizeZ/2, tableSizeX, tableSizeY, tableSizeZ, tableThickness);
Cuboid* room = new Cuboid(-roomSizeX / 2, -tableSizeY, -roomSizeZ / 2, roomSizeX, roomSizeY, roomSizeZ);


void RenderObjects(void)
{
    glPushMatrix(); 
        glPushMatrix(); 
            glColor4f(0.4, 0.37, 0.3, 1);
            room->draw();
            glColor4f(1, 1, 1, 1);
            dominoSet->draw();
            glTranslatef(0, -1, 0);
            table->draw();
        glPopMatrix(); 
    glPopMatrix();

}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    camera->refresh();
    RenderObjects();

    glutSwapBuffers();
    fflush(stdout);
}

void reshape(GLint width, GLint height)
{
    g_Width = width;
    g_Height = height;

    glViewport(0, 0, g_Width, g_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
    glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMaterialfv(GL_FRONT, GL_AMBIENT, g_lightPos);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);
}

void MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        g_bButtonLDown = (state == GLUT_DOWN) ? true : false;
        g_yClick = y;
        g_xClick = x;
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        g_bButtonRDown = (state == GLUT_DOWN) ? true : false;
        g_yClick = y;
    }
}

void MouseMotion(int x, int y)
{
    int deltaX = 0;
    int deltaY = 0;
    if (g_bButtonLDown)
    {
        deltaX = x - g_xClick;
        deltaY = y - g_yClick;
        camera->handleMouseMoved(GLUT_LEFT_BUTTON, deltaX, deltaY);       
    }
    else if (g_bButtonRDown)
    {
        deltaY = y - g_yClick;
        camera->handleMouseMoved(GLUT_RIGHT_BUTTON, deltaX, deltaY);
    }
    glutPostRedisplay();
    g_xClick = x;
    g_yClick = y;
}

void Keyboard(unsigned char key, int x, int y)
{
    camera->handleKeyboard(key);
    if (key == 'z')
    {
        dominoSet->start();
    }
    else if (key == 'x')
    {
        dominoSet->nextStep();
    }
    else if (key == 'p')
    {
        dominoSet->pause();
    }
    else if (key == '1')
    {
        dominoSet->loadDefaultSet(50);
    }
    else if (key == '2')
    {
        dominoSet->loadYSet(75);
    }
	else if (key == '3')
	{
		dominoSet->loadDiamondSet(80);
	}
    glutPostRedisplay();
}

void Update()
{
    dominoSet->nextStep();
    glutPostRedisplay();
}

void Scena::start(int argc, char** argv)
{
    g_lightPos[0] = roomSizeX / 2;
    g_lightPos[1] = roomSizeY/2;
    g_lightPos[2] = roomSizeX / 2;
    room->revert();
    // GLUT Window Initialization:
    glutInit(&argc, argv);
    glutInitWindowSize(g_Width, g_Height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Projekt AAL");
    room->setAllTex(TexType::Wall);
    room->setBotTex(TexType::Floor);
    // Initialize OpenGL graphics state
    InitGraphics();
    
    // Register callbacks:
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);
    glutIdleFunc(Update);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    // Turn the flow of control over to GLUT
    glutMainLoop();
}

void Scena::close()
{

}

