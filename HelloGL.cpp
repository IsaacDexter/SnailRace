#include "HelloGL.h"
#include <iostream>

/// <summary> static array containing all the vertices of a 1*1*1 cube</summary>
Vertex HelloGL::vertices[] = { 
	 1, 1, 1,	-1, 1, 1,	-1,-1, 1,	//v0-v1-v2 (front)
	-1,-1, 1,	 1,-1, 1,	 1, 1, 1,	//v2-v3-v0

	 1, 1, 1,	 1,-1, 1,	 1,-1,-1,	//v0-v3-v4 (right)
	 1,-1,-1,	 1, 1,-1,	 1, 1, 1,	//v4-v5-v0

	 1, 1, 1,	 1, 1,-1,	-1, 1,-1,	//v0-v5-v6 (top)
	-1, 1,-1,	-1, 1, 1,	 1, 1, 1,	//v6-v1-v0

	-1, 1, 1,	-1, 1,-1,	-1,-1,-1,	//v1-v6-v7 (left)
	-1,-1,-1,	-1,-1, 1,	-1, 1, 1,	//v7-v2-v1

	-1,-1,-1,	 1,-1,-1,	 1,-1, 1,	//v7-v4-v3 (bottom)
	 1,-1, 1,	-1,-1, 1,	-1,-1,-1,	//v3-v2-v7

	 1,-1,-1,	-1,-1,-1,	-1, 1,-1,	//v4-v7-v6 (back)
	-1, 1,-1,	 1, 1,-1,	 1,-1,-1,	//v6-v5-v4
};

/// <summary>Array containing all the colours at each vertex. Different to tutorial as simply recycled old values cuz lazy</summary>
Color HelloGL::colors[] = {
	 1, 1, 1,	 0, 1, 1,	 0, 0, 1,	//v0-v1-v2 (front)
	 0, 0, 1,	 1, 0, 1,	 1, 1, 1,	//v2-v3-v0

	 1, 1, 1,	 1, 0, 1,	 1, 0, 0,	//v0-v3-v4 (right)
	 1, 0, 0,	 1, 1, 0,	 1, 1, 1,	//v4-v5-v0

	 1, 1, 1,	 1, 1, 0,	 0, 1, 0,	//v0-v5-v6 (top)
	 0, 1, 0,	 0, 1, 1,	 1, 1, 1,	//v6-v1-v0

	 0, 1, 1,	 0, 1, 0,	 0, 0, 0,	//v1-v6-v7 (left)
	 0, 0, 0,	 0, 0, 1,	 0, 1, 1,	//v7-v2-v1

	 0, 0, 0,	 1, 0, 0,	 1, 0, 1,	//v7-v4-v3 (bottom)
	 1, 0, 1,	 0, 0, 1,	 0, 0, 0,	//v3-v2-v7

	 1, 0, 0,	 0, 0, 0,	 0, 1, 0,	//v4-v7-v6 (back)
	 0, 1, 0,	 1, 1, 0,	 1, 0, 0,	//v6-v5-v4
};

/// <summary>All 8 indexed vertices in the cube</summary>
Vertex HelloGL::indexedVertices[] = {
	 1, 1, 1,	//vertex 0
	-1, 1, 1,	//vertex 1
	-1,-1, 1,	//vertex 2
	 1,-1, 1,	//vertex 3
	 1,-1,-1,	//vertex 4
	 1, 1,-1,	//vertex 5
	-1, 1,-1,	//vertex 6
	-1,-1,-1	//vertex 7
};

/// <summary>The color associated with each vertex</summary>
Color HelloGL::indexedColors[] = {
	 1, 1, 1,	//vertex 0, white
	 0, 1, 1,	//vertex 1, cyan
	 0, 0, 1,	//vertex 2, blue
	 1, 0, 1,	//vertex 3, magenta
	 1, 0, 0,	//vertex 4, red
	 1, 1, 0,	//vertex 5, yellow
	 0, 1, 0,	//vertex 6, green
	 0, 0, 0	//vertex 7, black
};

/// <summary>Defines the triangles that make up the cube, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
GLushort HelloGL::indices[] = {
	0,	1,	2,		2,	3,	0,	//Front
	0,	3,	4,		4,	5,	0,	//Right
	0,	5,	6,		6,	1,	0,	//Top
	1,	6,	7,		7,	2,	1,	//Left
	7,	4,	3,		3,	2,	7,	//Bottom
	4,	7,	6,		6,	5,	4	//Back
};

HelloGL::HelloGL(int argc, char* argv[])
{
	//Initialises Glut
	glutInit(&argc, argv);
	//Initialise everything else
	GLUTCallbacks::Init(this);

	//set the size of the window in pixels
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//set the initial position of the window on the screen
	glutInitWindowPosition(100, 100);
	//The title of the window
	glutCreateWindow("HelloGL");
	glutDisplayFunc(GLUTCallbacks::Display);
	//16: how long timer should weight before calling the method (REFRESHRATE = 16ms * 60 ~= 1000ms, so 60fps). Timer: Method to be called. 16: Parameter passed into timer method (prefferedRefresh) (16ms again)
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	//glutKeyboardFunc sets the keyboard callback for the current window, so must be after createwindow. Tells glut freeglut about the Keyboard method.
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	//glutMotionFunc sets mouse callback for current window as well. Used to rotate objects on screen
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	//glutPassiveMotionFunc - like glutMotionFunc but calls even when buttons aren't pressed. Used to update mouse position
	glutPassiveMotionFunc(GLUTCallbacks::PassiveMouseMotion);
	//glutMouseFunc used to handle click events
	glutMouseFunc(GLUTCallbacks::MouseButton);

	//Sets display mode to double buffering, which eliminates 'flickering'.
	glutInitDisplayMode(GLUT_DOUBLE);
	//Enables back face culling, which obscures back faces of shapes that are not in view, giving a true perspective
	glEnable(GL_CULL_FACE);
	//Tells OpenGL which faces to cull, in this case, (and most cases,) back.
	glCullFace(GL_BACK);

	//Create a new camera and initialise it
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	//Create a new vector2 representing the mouse location and initialise it
	_oldMousePos = new Vector2();

	//Create a new Vector 3 representing rotation in each axis
	_rotationAxes = new Vector3();

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
	glPushMatrix();
		glRotatef(_rotationAxes->x, -1.0f, 0.0f, 0.0f);	//Rotate in the x by the x rotation
		glRotatef(_rotationAxes->y, 0.0f, -1.0f, 0.0f);	//Rotate in the y by the y rotation
		glRotatef(_rotationAxes->z, 0.0f, 0.0f, -1.0f);	//Rotate in the z by the z rotation
		//glutWireTeapot(0.1);
		DrawIndexedCube();
	glPopMatrix();

	//And ends here:

	glFlush();	//Flushes scene to the graphics card
	glutSwapBuffers();	//Tell freeGLut to swap the buffers.
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//Toggles between various camera view modes. These are used to experiment with the camera, as I do not understand how it works
	if (key == ' ')
	{
		viewMode += 1;
		if (viewMode > 3)
		{
			viewMode = 1;
		}
	}
	switch (viewMode)
	{
	case 1:
		switch (key)
		{
		case 'w':
			camera->center.y -= 0.0125f;
			break;
		case 'a':
			camera->center.x -= 0.0125f;
			break;
		case 's':
			camera->center.y += 0.0125f;
			break;
		case 'd':
			camera->center.x += 0.0125f;
			break;
		case 'q':
			camera->center.z += 0.0125f;
			break;
		case 'e':
			camera->center.z -= 0.0125f;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (key)
		{
		case 'w':
			camera->eye.y -= 0.025f;
			break;
		case 'a':
			camera->eye.x -= 0.025f;
			break;
		case 's':
			camera->eye.y += 0.025f;
			break;
		case 'd':
			camera->eye.x += 0.025f;
			break;
		case 'q':
			camera->eye.z += 0.025f;
			break;
		case 'e':
			camera->eye.z -= 0.025f;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (key)
		{
		case 'w':
			camera->up.y -= 0.05f;
			break;
		case 'a':
			camera->up.x -= 0.05f;
			break;
		case 's':
			camera->up.y += 0.05f;
			break;
		case 'd':
			camera->up.x += 0.05f;
			break;
		case 'q':
			camera->up.z += 0.05f;
			break;
		case 'e':
			camera->up.z -= 0.05f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

///<summary>Calls the mouses position when a mouse button is held. Used to rotate the teapot<\summary>
void HelloGL::MouseMotion(int x, int y)
{
	switch (_mouseButtonPressed)
	{
	case none:
		break;
	case LeftMouseButton:
		_rotationAxes->x += _oldMousePos->y - y;	//In lmb mode, pitch object forward/back
		_rotationAxes->y += _oldMousePos->x - x;	//Yaw object to the left and right
		break;
	case RightMouseButton:
		_rotationAxes->z += _oldMousePos->x - x;	//roll object starboard and port
		break;
	default:
		break;
	}
	//Update mouse position, as passive does not call when motion is called
	_oldMousePos->x = x, _oldMousePos->y = y;
}

/// <summary>Calls whenever the mouse moves. Used to update the mouse's position</summary>
void HelloGL::PassiveMouseMotion(int x, int y)
{
	_oldMousePos->x = x, _oldMousePos->y = y;
	//std::cout << "Mouse Pos: x = " << _oldMousePos->x << ", y = " << _oldMousePos->y << std::endl;
}

void HelloGL::MouseButton(int button, int state, int x, int y)
{
	switch (state)
	{
	case GLUT_DOWN:
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			_mouseButtonPressed = LeftMouseButton;
			break;
		case GLUT_RIGHT_BUTTON:
			_mouseButtonPressed = RightMouseButton;
			break;
		case GLUT_MIDDLE_BUTTON:
			_mouseButtonPressed = MiddleMouseButton;
			//Reset Rotation
			_rotationAxes->x = 0.0f; //Reset pitch as mmb mode
			_rotationAxes->y = 0.0f; //Reset yaw as mmb mode
			_rotationAxes->z = 0.0f; //Reset roll as mmb mode
			//Reset Camera Position
			camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
			camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
			camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		_mouseButtonPressed = none;
		break;
	default:
		break;
	}
}

/// <summary>Calls each frame. Updates each aspect of the game</summary>
void HelloGL::Update()
{
	//Rest our modelview matrix , so all transformations from previous frames arent included in the current one
	glLoadIdentity();

	//move the camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	

	//Update the rotation of the rectangle
	/*if (_rectangleRotation <= 360.0f)
	{
		_rectangleRotation += 0.5f;
	}
	else
	{
		_rectangleRotation = 0.0f;
	}*/

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

	glBegin(GL_POLYGON);	//Tells GL to expect polygon vertices until the glEnd.
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);	//Indents not required. all drawing commands will be of this colour until next specified change. Args are (R, G, B, A).
	glVertex2f(0.75, 0.5);	//Args are x and y, repectively. Remember the origin is in the center and the far edges of the screen are -1, 1, 1, -1 respectively, making this the top left corner.
	glVertex2f(0.75, -0.5);	//Top right
	glVertex2f(-0.75, -0.5);	//Top left
	glVertex2f(-0.75, 0.5); //Bottom left
	glEnd();	//Defines the end of the polygon

	glPopMatrix();	//Isolate matrix calculations ('}')
}

void HelloGL::DrawCube(float sf)
{
	glBegin(GL_TRIANGLES);

	//face v0-v1-v2
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	glColor3f(1, 1, 0);			//vertex 1 colours
	glVertex3f(-sf, sf, sf);	//vertex 1 point
	glColor3f(1, 0, 0);			//vertex 2 colours
	glVertex3f(-sf, -sf, sf);	//vertex 2 point
	//face v2-v3-v0
	glColor3f(1, 0, 0);			//vertex 2 colours
	glVertex3f(-sf, -sf, sf);	//vertex 2 point
	glColor3f(1, 0, 1);			//vertex 3 colours
	glVertex3f(sf, -sf, sf);	//vertex 3 point
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	//face v0-v3-v4
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	glColor3f(1, 0, 1);			//vertex 3 colours
	glVertex3f(sf, -sf, sf);	//vertex 3 point
	glColor3f(0, 0, 1);			//vertex 4 colours
	glVertex3f(sf, -sf, -sf);	//vertex 4 point
	//face v4-v5-v0
	glColor3f(0, 0, 1);			//vertex 4 colours
	glVertex3f(sf, -sf, -sf);	//vertex 4 point
	glColor3f(1, 0, 1);			//vertex 5 colours
	glVertex3f(sf, sf, -sf);	//vertex 5 point
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	//face v0-v5-v6
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	glColor3f(1, 0, 1);			//vertex 5 colours
	glVertex3f(sf, sf, -sf);	//vertex 5 point
	glColor3f(0, 1, 0);			//vertex 6 colours
	glVertex3f(-sf, sf, -sf);	//vertex 6 point
	//face v6-v1-v0
	glColor3f(0, 1, 0);			//vertex 6 colours
	glVertex3f(-sf, sf, -sf);	//vertex 6 point
	glColor3f(1, 1, 0);			//vertex 1 colours
	glVertex3f(-sf, sf, sf);	//vertex 1 point
	glColor3f(1, 1, 1);			//vertex 0 colours
	glVertex3f(sf, sf, sf);		//vertex 0 point
	//face v1-v6-v7
	glColor3f(1, 1, 0);			//vertex 1 colours
	glVertex3f(-sf, sf, sf);	//vertex 1 point
	glColor3f(0, 1, 0);			//vertex 6 colours
	glVertex3f(-sf, sf, -sf);	//vertex 6 point
	glColor3f(0, 0, 0);			//vertex 7 colours
	glVertex3f(-sf, -sf, -sf);	//vertex 7 point
	//face v7-v2-v1
	glColor3f(0, 0, 0);			//vertex 7 colours
	glVertex3f(-sf, -sf, -sf);	//vertex 7 point
	glColor3f(1, 0, 0);			//vertex 2 colours
	glVertex3f(-sf, -sf, sf);	//vertex 2 point
	glColor3f(1, 1, 0);			//vertex 1 colours
	glVertex3f(-sf, sf, sf);	//vertex 1 point
	//face v7-v4-v3
	glColor3f(0, 0, 0);			//vertex 7 colours
	glVertex3f(-sf, -sf, -sf);	//vertex 7 point
	glColor3f(0, 0, 1);			//vertex 4 colours
	glVertex3f(sf, -sf, -sf);	//vertex 4 point
	glColor3f(1, 0, 1);			//vertex 3 colours
	glVertex3f(sf, -sf, sf);	//vertex 3 point
	//face v3-v2-v7
	glColor3f(1, 0, 1);			//vertex 3 colours
	glVertex3f(sf, -sf, sf);	//vertex 3 point
	glColor3f(1, 0, 0);			//vertex 2 colours
	glVertex3f(-sf, -sf, sf);	//vertex 2 point
	glColor3f(0, 0, 0);			//vertex 7 colours
	glVertex3f(-sf, -sf, -sf);	//vertex 7 point
	//face v4-v7-v6
	glColor3f(0, 0, 1);			//vertex 4 colours
	glVertex3f(sf, -sf, -sf);	//vertex 4 point
	glColor3f(0, 0, 0);			//vertex 7 colours
	glVertex3f(-sf, -sf, -sf);	//vertex 7 point
	glColor3f(0, 1, 0);			//vertex 6 colours
	glVertex3f(-sf, sf, -sf);	//vertex 6 point
	//face v6-v5-v4
	glColor3f(0, 1, 0);			//vertex 6 colours
	glVertex3f(-sf, sf, -sf);	//vertex 6 point
	glColor3f(1, 0, 1);			//vertex 5 colours
	glVertex3f(sf, sf, -sf);	//vertex 5 point
	glColor3f(0, 0, 1);			//vertex 4 colours
	glVertex3f(sf, -sf, -sf);	//vertex 4 point

	glEnd();
}

void HelloGL::DrawCubeArray(float sf)
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		glVertex3f(vertices[i].x * sf, vertices[i].y * sf, vertices[i].z * sf);
	}
	glEnd();

	glPopMatrix();
}

void HelloGL::DrawIndexedCube(float sf)
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&indexedColors[indices[i]].r);
		glVertex3f(indexedVertices[indices[i]].x * sf, indexedVertices[indices[i]].y * sf, indexedVertices[indices[i]].z * sf);
	}

	glEnd();

	glPopMatrix();
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