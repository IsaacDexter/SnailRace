#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
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
	glBegin(GL_POLYGON);	//Tells GL to expect polygon vertices until the glEnd.
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);	//Indents not required. all drawing commands will be of this colour until next specified change. Args are (R, G, B, A).
		glVertex2f(-0.75, 0.5);	//Args are x and y, repectively. Remember the origin is in the center and the far edges of the screen are -1, 1, 1, -1 respectively, making this the top left corner.
		glVertex2f(0.75, 0.5);	//Top right
		glVertex2f(0.75, -0.5);	//Top left
		glVertex2f(-0.75, -0.5); //Bottom left
		glEnd();	//Defines the end of the polygon
		glFlush();	//Flushes scene to the graphics card
}

HelloGL::~HelloGL(void)
{

}