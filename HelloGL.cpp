#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	//Initialise variables
	_rectangleRotation = 0.0f;

	//Initialise everything else
	GLUTCallbacks::Init(this);
	glutInitDisplayMode(GLUT_DOUBLE);	//Sets display mode to double buffering, which eliminates 'flickering'.
	glutInit(&argc, argv);
	//set the size of the window in pixels
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//set the initial position of the window on the screen
	glutInitWindowPosition(100, 100);
	//The title of the window
	glutCreateWindow("HelloGL");
	glutDisplayFunc(GLUTCallbacks::Display);
	//16: how long timer should weight before calling the method (REFRESHRATE = 16ms * 60 ~= 1000ms, so 60fps). Timer: Method to be called. 16: Parameter passed into timer method (prefferedRefresh) (16ms again)
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	//Create a new camera and initialise it
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	//Tell openGl to switch to a different set of matrixes, to work with a different part of the transformation pipleine
	glMatrixMode(GL_PROJECTION);
	//Loads the identity matrix, think of setting the matrix back to 1
	glLoadIdentity();
	//set the viewport to take the entirity of the window
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Set up the camera. Parameters are F.O.V. , Aspect ratio, near clipping distance, far clipping distance
	gluPerspective(45, 1, 0, 1000);
	//Switch back to the model view matrix to work with models again
	glMatrixMode(GL_MODELVIEW);

	//start the main loop
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

	//And ends here:

	glFlush();	//Flushes scene to the graphics card
	glutSwapBuffers();	//Tell freeGLut to swap the buffers.
}

/// <summary>Calls each frame. Updates each aspect of the game</summary>
void HelloGL::Update()
{
	//Rest our modelview matrix , so all transformations from previous frames arent included in the current one
	glLoadIdentity();

	//move the camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	

	//Update the rotation of the rectangle
	if (_rectangleRotation <= 360.0f)
	{
		_rectangleRotation += 0.5f;
	}
	else
	{
		_rectangleRotation = 0.0f;
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

	//It is worth noting that irder of operation is important, as transformation calls are dealt with IN REVERSE ORDER

	//Translate the object down the z axis
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(_rectangleRotation, 1.0f, 0.0f, 0.0f);	//Rotate by rotation solely around the Z axis.

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
	delete camera;
}