#include "HelloGL.h"
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();
	InitLighting(Vector3(1.4f, 0.0f, 0.0f), Vector4(0.2f, 0.2f, 0.4f, 1.0f), Vector4(0.3f, 0.3f, 0.6f, 1.0f), Vector4(0.4f, 0.4f, 0.8f, 1.0f));
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
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

	//Sets display mode to double buffering, which eliminates 'flickering'. | GLUT_DEPTH adds z-buffering, so objects can appear to obscure as opposed to overlap eachother
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	//Without this nothing witll be textured, and you will be left with white faces.
	glEnable(GL_TEXTURE_2D);
	//Enables back face culling, which obscures back faces of shapes that are not in view, giving a true perspective
	glEnable(GL_CULL_FACE);
	//Enables depth testing, with obscures shapes that are hidden from view by shapes in front of them.
	glEnable(GL_DEPTH_TEST);
	//Enables the lighting mode, which lets us light shapes
	glEnable(GL_LIGHTING);
	//enables the first of the 8 lights.
	glEnable(GL_LIGHT0);
	//Tells OpenGL which faces to cull, in this case, (and most cases,) back.
	glCullFace(GL_BACK);

	//Create a new vector2 representing the mouse location and initialise it
	g_oldMousePos = new Vector2();

	//Create a new Vector 3 representing rotation in each axis
	g_rotationAxes = new Vector3();

	//Tell openGl to switch to a different set of matrixes, to work with a different part of the transformation pipleine
	glMatrixMode(GL_PROJECTION);
	//Loads the identity matrix, think of setting the matrix back to 1
	glLoadIdentity();
	//set the viewport to take the entirity of the window
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Set up the camera. Parameters are F.O.V. , Aspect ratio, near clipping distance, far clipping distance
	gluPerspective(45, 1, 1, 1000);
	//Switch back to the model view matrix to work with models again
	glMatrixMode(GL_MODELVIEW);

	
}
/// <summary>Initialises the camera, textures and any meshes in the scene</summary>
void HelloGL::InitObjects()
{
	//Initialise the linked list to contain the scene objects, and set us to be using the first object in the list.
	g_sceneObjectsList = new LinkedLists();
	g_head = nullptr;
	g_currentSceneObjectLocation = 0;

	//Create a new camera and initialise it
	g_camera = new Camera();
	g_camera->eye.x = 0.0f; g_camera->eye.y = 0.0f; g_camera->eye.z = 1.0f;
	g_camera->center.x = 0.0f; g_camera->center.y = 0.0f; g_camera->center.z = 0.0f;
	g_camera->up.x = 0.0f; g_camera->up.y = 1.0f; g_camera->up.z = 0.0f;

	//Load Textures
	g_penguinTexture = new Texture2D();
	g_penguinTexture->Load((char*)"Textures/penguins.raw", 512, 512);

	g_brickTexture = new Texture2D();
	g_brickTexture->LoadBMP((char*)"Textures/Brick.bmp");

	//Loads Materials
	g_brickMaterial = new Material(Vector4(0.8f, 0.05f, 0.05f, 1.0f), Vector4(0.8f, 0.05f, 0.05f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 100.0f);
	g_penguinMaterial = new Material(Vector4(0.4f, 0.4f, 0.45f, 1.0f), Vector4(0.4f, 0.4f, 0.45f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 100.0f);

	//Load Meshes
	g_cubeMesh = MeshLoader::Load((char*)"Models/cube.txt");
	g_hexagonalPrismMesh = MeshLoader::Load((char*)"Models/hexagonalPrism.txt");

	//Mesh* squareBasedPyramidMesh = MeshLoader::Load((char*)"Models/squareBasedPyramid.txt");
	
	//Adds meshes textures and materials into SceneObjects/Primitives at locations specified.
	//g_cube = new Primitive(cubeMesh, brickTexture, brickMaterial, 0.0f, 0.0f, -1.0f);
	//g_hexagonalPrism = new Primitive(hexagonalPrismMesh, penguinTexture, penguinMaterial, 0.0f, 1.0f, 0.0f);
	//g_squareBasedPyramid = new Primitive(squareBasedPyramidMesh, penguinTexture, 0.0f, 0.0f, -1.0f);

	//Adds scene objects / primitives into the linked list.
	//g_sceneObjectsList->AppendNode(&g_head, new Primitive(g_cubeMesh, g_brickTexture, g_brickMaterial, 0.0f, 0.0f, -1.0f));
	g_sceneObjectsList->AppendNode(&g_head, new Primitive(g_hexagonalPrismMesh, g_penguinTexture, g_penguinMaterial, 0.0f, 1.0f, 0.0f));
}

/// <summary>Initialises a light within the scene, GL_LIGHT0</summary>
/// <param name="lightPosition">The position of the light as a vector3</param>
/// <param name="ambient">The ambient value of the light, as a vector4</param>
/// <param name="diffuse">The diffuse value of the light, as a vector4</param>
/// <param name="specular">The specular value of the light, as a vector4</param>
void HelloGL::InitLighting(Vector3 lightPosition, Vector4 ambient, Vector4 diffuse, Vector4 specular)
{
	g_lightPosition = new Vector4(lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);
	g_lightData = new Lighting();
	g_lightData->Ambient = ambient;
	g_lightData->Diffuse = diffuse;
	g_lightData->Specular = specular;
}

void HelloGL::InitMaterials()
{

}



/// <summary>
/// Place drawing code in here. Not called automatically, only when requested (including automatic initial request
/// </summary>
void HelloGL::Display()
{
	//Steps: clear existing scene, begin drawing, draw object, end drwaing, flush to graphics card.
	//Draw simple rectangle
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clears the scene
	
	Vector3 v = { -1.4f, 0.7f, -1.0f };
	Color c = { 197.0f, 5.0f, 255.0f };
	DrawString((char*)"I LOVE LEAN!!!!!", &v, &c);
	//Drawing code goes here:
	glPushMatrix();
		//switch (g_currentShape)
		//{
		//case cube:
		//	g_cube->Update();
		//	g_cube->Draw();
		//	break;
		//case hexagonalPrism:
		//	g_hexagonalPrism->Update();
		//	g_hexagonalPrism->Draw();
		//	break;
		//case squareBasedPyramid:
		//	g_squareBasedPyramid->Update();
		//	g_squareBasedPyramid->Draw();
		//	break;
		//case all:
		//	g_cube->Update();
		//	g_cube->Draw();
		//	g_hexagonalPrism->Update();
		//	g_hexagonalPrism->Draw();
		//	g_squareBasedPyramid->Update();
		//	g_squareBasedPyramid->Draw();
		//	break;
		//default:
		//	break;
		//}
	
	//draw all the objects in the g_sceneObjectsList
	g_sceneObjectsList->RenderList(g_head);
	//g_sceneObjectsList->GetNode(g_head, g_currentSceneObjectLocation)->sceneObject->Draw();
	glPopMatrix();

	//And ends here:

	glFlush();	//Flushes scene to the graphics card
	glutSwapBuffers();	//Tell freeGLut to swap the buffers.
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);	//The raster position on the screen which we manupulate with the translate
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);	//Thakes the font type and the string to display

	glPopMatrix();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//Toggles between various camera view modes. These are used to experiment with the camera, as I do not understand how it works
	if (key == ' ')
	{
		g_viewMode += 1;
		if (g_viewMode > 3)
		{
			g_viewMode = 1;
		}
	}

	//Code for switching between 10 shapes.
	if (isdigit(key))
	{
		//Treat 0 as a 10.
		if (key == '0')
		{
			key += 10;
		}
		//Allows the user to switch between objects in the list, but makes sure they cannot exceed the length of the list.
		g_currentSceneObjectLocation = min(int(key) - 49, g_sceneObjectsList->GetListLength(g_head) - 1);
		//Get the rotation axes of the current shape in the list. Allows different shapes in the linked list to have different rotations.
		g_rotationAxes = g_sceneObjectsList->GetNode(g_head, g_currentSceneObjectLocation)->sceneObject->GetRotation();
	}

	if (key == 'n')
	{
		g_sceneObjectsList->InsertAfter(g_sceneObjectsList->GetNode(g_head, g_currentSceneObjectLocation), new Primitive(g_cubeMesh, g_penguinTexture, g_penguinMaterial, 0.0f, 0.0f, 0.0f));
		g_currentSceneObjectLocation++;
		g_rotationAxes = g_sceneObjectsList->GetNode(g_head, g_currentSceneObjectLocation)->sceneObject->GetRotation();
	}

	switch (g_viewMode)
	{
	case 1:
		switch (key)
		{
		case 'w':	//Pan camera up
			g_camera->center.y -= 0.0125f;
			break;
		case 'a':	//pan camera left
			g_camera->center.x -= 0.0125f;
			break;
		case 's':	//pan camera down
			g_camera->center.y += 0.0125f;
			break;
		case 'd':	//Pan camera right
			g_camera->center.x += 0.0125f;
			break;
		case 'q':	//?
			g_camera->center.z += 0.0125f;
			break;
		case 'e':	//?
			g_camera->center.z -= 0.0125f;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (key)
		{
		case 'w':	//?
			g_camera->eye.y -= 0.025f;
			break;
		case 'a':	//?
			g_camera->eye.x -= 0.025f;
			break;
		case 's':	//?
			g_camera->eye.y += 0.025f;
			break;
		case 'd':	//?
			g_camera->eye.x += 0.025f;
			break;
		case 'q':	//move camera away from origin
			g_camera->eye.z += 0.25f;
			break;
		case 'e':	//move camera towards origin
			g_camera->eye.z -= 0.25f;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (key)
		{
		case 'w':	//?
			g_camera->up.y -= 0.05f;
			break;
		case 'a':	//?
			g_camera->up.x -= 0.05f;
			break;
		case 's':	//?
			g_camera->up.y += 0.05f;
			break;
		case 'd':	//?
			g_camera->up.x += 0.05f;
			break;
		case 'q':	//?
			g_camera->up.z += 0.05f;
			break;
		case 'e':	//?
			g_camera->up.z -= 0.05f;
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
	switch (g_mouseButtonPressed)
	{
	case none:
		break;
	case LeftMouseButton:
		g_rotationAxes->x += g_oldMousePos->y - y;	//In lmb mode, pitch object forward/back
		g_rotationAxes->y += g_oldMousePos->x - x;	//Yaw object to the left and right
		break;
	case RightMouseButton:
		g_rotationAxes->z += g_oldMousePos->x - x;	//roll object starboard and port
		break;
	default:
		break;
	}
	//Update mouse position, as passive does not call when motion is called
	g_oldMousePos->x = x, g_oldMousePos->y = y;
}

/// <summary>Calls whenever the mouse moves. Used to update the mouse's position</summary>
void HelloGL::PassiveMouseMotion(int x, int y)
{
	g_oldMousePos->x = x, g_oldMousePos->y = y;
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
			g_mouseButtonPressed = LeftMouseButton;
			break;
		case GLUT_RIGHT_BUTTON:
			g_mouseButtonPressed = RightMouseButton;
			break;
		case GLUT_MIDDLE_BUTTON:
			g_mouseButtonPressed = MiddleMouseButton;
			//Reset Rotation
			g_rotationAxes->x = 0.0f; //Reset pitch as mmb mode
			g_rotationAxes->y = 0.0f; //Reset yaw as mmb mode
			g_rotationAxes->z = 0.0f; //Reset roll as mmb mode
			//Reset Camera Position
			g_camera->eye.x = 0.0f; g_camera->eye.y = 0.0f; g_camera->eye.z = 1.0f;
			g_camera->center.x = 0.0f; g_camera->center.y = 0.0f; g_camera->center.z = 0.0f;
			g_camera->up.x = 0.0f; g_camera->up.y = 1.0f; g_camera->up.z = 0.0f;
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		g_mouseButtonPressed = none;
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
	gluLookAt(g_camera->eye.x, g_camera->eye.y, g_camera->eye.z, g_camera->center.x, g_camera->center.y, g_camera->center.z, g_camera->up.x, g_camera->up.y, g_camera->up.z);
	
	//Sets the lighting data for light0. Dne every frame in the update function, so if the light changes on runtime, the program handles accordingly (e.g. light turns off, etc.)
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(g_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(g_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(g_lightData->Specular.x));
	//Sets light0's position.
	glLightfv(GL_LIGHT0, GL_POSITION, &(g_lightPosition->x));

	//Rotate the current shape
	//switch (g_currentShape)
	//{
	//case cube:
	//	g_cube->SetRotation(g_rotationAxes->x, g_rotationAxes->y, g_rotationAxes->z);
	//	break;
	//case hexagonalPrism:
	//	g_hexagonalPrism->SetRotation(g_rotationAxes->x, g_rotationAxes->y, g_rotationAxes->z);
	//	break;
	//case squareBasedPyramid:
	//	g_squareBasedPyramid->SetRotation(g_rotationAxes->x, g_rotationAxes->y, g_rotationAxes->z);
	//	break;
	//default:
	//	break;
	//}

	g_sceneObjectsList->GetNode(g_head, g_currentSceneObjectLocation)->sceneObject->SetRotation(g_rotationAxes->x, g_rotationAxes->y, g_rotationAxes->z);
	//Update all of the sceneObjects
	g_sceneObjectsList->UpdateList(g_head);

	glutPostRedisplay();
}

HelloGL::~HelloGL(void)
{
	delete g_camera;
	delete g_oldMousePos;
	delete g_rotationAxes;

}