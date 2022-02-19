#pragma once
#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include "GLUTCallbacks.h"


//Defs
#define REFRESHRATE 16
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


/// <summary>
/// Simple enum used to store different triangle types.
/// </summary>
enum TriangleTypes
{
	Scalene = 1,
	Isoceles,
	Equilateral,
};

enum MouseButtons
{
	none,
	LeftMouseButton,
	RightMouseButton,
	MiddleMouseButton,
};

/// <summary>A 3D vector represeting a single point in space</summary>
struct Vector3
{
	float x;
	float y;
	float z;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	//Allows us to take parameters, so we can construct with any values
	Vector3(float initial_x, float initial_y, float initial_z)
	{
		x = initial_x;
		y = initial_y;
		z = initial_z;
	}
};

struct Vector2
{
	float x;
	float y;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	//Allows us to take parameters, so we can construct with any values
	Vector2(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

/// <summary>Used to store colours for each vertex in a 3D shape. uses GLfloat to avoid compiler warnings</summary>
struct Color
{
	GLfloat r, g, b;
};

/// <summary>Used to store vertexes in a 3D shape. uses GLfloat to avoid compiler warnings</summary>
struct Vertex
{
	GLfloat x, y, z;
};

class HelloGL
{
public:
	//Constructor def
	HelloGL(int argc, char* argv[]);


	//Destructor def
	~HelloGL(void);

	//Display methods
	void DrawRectangle();
	/// <summary>Draws a multicoloured cube.</summary>
	/// <param name="sf">The scale factor</param>
	void DrawCube(float sf = 0.1f);
	void DrawTriangle(TriangleTypes triangleType);
	void Display();
	/// <summary>Method used to draw a cube from a vertex and colour array.</summary>
	void DrawCubeArray(float sf = 0.1f);

	//Input Methods
	void Keyboard(unsigned char key, int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void PassiveMouseMotion(int x, int y);

	//Update methods
	void Update();
private:
	/// <summary>1 for center, 2 for eye, 3 for up</summary>
	int viewMode = 1;
	Camera* camera;
	/// <summary>Vector2 storing mouse position</summary>
	Vector2* _oldMousePos;
	/// <summary>Vector3 representing the rotation in each axis</summary>
	Vector3* _rotationAxes;

	/// <summary>Static for now to allow for easy initialisation, but this will most likely be changed when starting to load files</summary>
	static Vertex vertices[];
	static Color colors[];

	MouseButtons _mouseButtonPressed = none;
};