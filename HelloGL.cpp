#include "HelloGL.h"
#include <iostream>

/// <summary> static array containing all the vertices of a 1*1*1 cube</summary>
Vertex HelloGL::cube_vertices[] = { 
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
Color HelloGL::cube_colors[] = {
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

	//Load shapes
	_cube = new Cube();
	_hexagonalPrism = new HexagonalPrism();
	_squareBasedPyramid = new SquareBasedPyramid();

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
		//glutWireTeapot(0.1);
		switch (_currentShape)
		{
		case cube:
			_cube->Update(_rotationAxes);
			_cube->Draw();
			break;
		case hexagonalPrism:
			_hexagonalPrism->Update(_rotationAxes);
			_hexagonalPrism->Draw();
			break;
		case squareBasedPyramid:
			_squareBasedPyramid->Update(_rotationAxes);
			_squareBasedPyramid->Draw();
			break;
		default:
			break;
		}
		
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

	switch (key)
	{
	case '1':
		_currentShape = cube;
		break;
	case '2':
		_currentShape = hexagonalPrism;
		break;
	case '3':
		_currentShape = squareBasedPyramid;
		break;
	default:
		break;
	}

	switch (viewMode)
	{
	case 1:
		switch (key)
		{
		case 'w':	//Pan camera up
			camera->center.y -= 0.0125f;
			break;
		case 'a':	//pan camera left
			camera->center.x -= 0.0125f;
			break;
		case 's':	//pan camera down
			camera->center.y += 0.0125f;
			break;
		case 'd':	//Pan camera right
			camera->center.x += 0.0125f;
			break;
		case 'q':	//?
			camera->center.z += 0.0125f;
			break;
		case 'e':	//?
			camera->center.z -= 0.0125f;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (key)
		{
		case 'w':	//?
			camera->eye.y -= 0.025f;
			break;
		case 'a':	//?
			camera->eye.x -= 0.025f;
			break;
		case 's':	//?
			camera->eye.y += 0.025f;
			break;
		case 'd':	//?
			camera->eye.x += 0.025f;
			break;
		case 'q':	//move camera away from origin
			camera->eye.z += 0.25f;
			break;
		case 'e':	//move camera towards origin
			camera->eye.z -= 0.25f;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (key)
		{
		case 'w':	//?
			camera->up.y -= 0.05f;
			break;
		case 'a':	//?
			camera->up.x -= 0.05f;
			break;
		case 's':	//?
			camera->up.y += 0.05f;
			break;
		case 'd':	//?
			camera->up.x += 0.05f;
			break;
		case 'q':	//?
			camera->up.z += 0.05f;
			break;
		case 'e':	//?
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
	
	glutPostRedisplay();
}

void HelloGL::DrawCubeArrayAlt(float sf)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
	glColorPointer(3, GL_FLOAT, 0, cube_colors);

	glPushMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

HelloGL::~HelloGL(void)
{
	delete camera;
	delete _oldMousePos;
	delete _rotationAxes;
}