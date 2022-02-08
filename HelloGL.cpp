#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	//Initialise variables
	_rotation = 0.0f;

	//Initialise everything else
	GLUTCallbacks::Init(this);
	glutInitDisplayMode(GLUT_DOUBLE);	//Sets display mode to double buffering, which eliminates 'flickering'.
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HelloGL");
	glutDisplayFunc(GLUTCallbacks::Display);
	//16: how long timer should weight before calling the method (REFRESHRATE = 16ms * 60 ~= 1000ms, so 60fps). Timer: Method to be called. 16: Parameter passed into timer method (prefferedRefresh) (16ms again)
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutMainLoop();
}

/// <summary>
/// Place drawing code in here. Not called automatically, only when requested (including automatic initial request
/// </summary>
void HelloGL::Display()
{
	//Steps: clear existing scene, begin drawing, draw object, end drwaing, flush to graphics card.
	//Draw simple rectangle
	glClear(GL_COLOR_BUFFER_BIT);	//Clears the scene
	
	//Drawing code goes here:

	DrawRectangle();
	DrawTriangle(Scalene);
	DrawTriangle(Isoceles);
	DrawTriangle(Equilateral);

	//And ends here:

	glFlush();	//Flushes scene to the graphics card
	glutSwapBuffers();	//Tell freeGLut to swap the buffers.
}

/// <summary>Calls each frame. Updates each aspect of the game</summary>
void HelloGL::Update()
{
	if (_rotation <= 360.0f)
	{
		_rotation += 0.5f;
	}
	else
	{
		_rotation = 0.0f;
	}

	//Calls the scene to redraw itself after the update has finished.
	glutPostRedisplay();
}

/// <summary>
/// Draws a simple red rectangle when called. Does not clear or flush.
/// </summary>
void HelloGL::DrawRectangle()
{
	glPushMatrix();	//Isolate matrix calculations ('{')
	glRotatef(_rotation, 0.0f, 0.0f, -1.0f);	//Rotate by rotation solely around the Z axis.

	glBegin(GL_POLYGON);	//Tells GL to expect polygon vertices until the glEnd.
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);	//Indents not required. all drawing commands will be of this colour until next specified change. Args are (R, G, B, A).
	glVertex2f(0.75, 0.5);	//Args are x and y, repectively. Remember the origin is in the center and the far edges of the screen are -1, 1, 1, -1 respectively, making this the top left corner.
	glVertex2f(0.75, -0.5);	//Top right
	glVertex2f(-0.75, -0.5);	//Top left
	glVertex2f(-0.75, 0.5); //Bottom left
	glEnd();	//Defines the end of the polygon

	glPopMatrix();	//Isolate matrix calculations ('}')
}

void HelloGL::DrawTriangle(TriangleTypes triangleType)
{
	glBegin(GL_POLYGON);	//Tells GL to expect polygon vertices until the glEnd.
	switch (triangleType)
	{
	case Scalene:
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);	//Blue
		glVertex2f(-1, 1);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);	//Green
		glVertex2f(-0.4, 1);	
		glColor4f(0.9f, 0.8f, 1.0f, 0.0f);	//Yellow
		glVertex2f(-0.35, 0.5);	
		break;
	case Isoceles:
		glColor4f(1.0f, 0.8f, 0.0f, 0.0f);	//Yellow
		glVertex2f(1, 1);
		glVertex2f(0.5, 1);
		glVertex2f(0.75, 0.25);
		break;
	case Equilateral:
		glColor4f(1.0f, 0.7f, 0.7f, 0.0f);	//Pink
		glVertex2f(-0.75, -1);
		glVertex2f(-1, -0.567);
		glVertex2f(-0.5, -0.567);
		break;
	default:
		break;
	}
	glEnd();
}

HelloGL::~HelloGL(void)
{

}