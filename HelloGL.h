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
	
	void DrawTriangle(TriangleTypes triangleType);
	void Display();
	/// <summary>Draws a multicoloured cube using hard coded values.</summary>
	/// <param name="sf">The scale factor</param>
	void DrawCube(float sf = 0.1f);
	/// <summary>Method used to draw a cube from a vertex and colour array.</summary>
	/// <param name="sf">The scale factor. Defaults to 0.1.</param>
	void DrawCubeArray(float sf = 0.1f);
	/// <summary>Draws cube using alternative built in method included. Does not support scale factor yet.</summary>
	/// <param name="sf">Nonfunctional.</param>
	void DrawCubeArrayAlt(float sf = 1.0f);
	/// <summary>The most memory and line efficient of the 3 methods. Uses indexed vertices and colors, as well as an indices array</summary>
	/// <param name="sf">The scale factor. Defaults to 0.1</param>
	void DrawIndexedCube(float sf = 0.1f);
	/// <summary>Draws indexed cube using alternative built in method included. DOes not support scale factor yet.</summary>
	/// <param name="sf">Nonfuctional</param>
	void DrawIndexedCubeAlt(float sf = 1.0f);
	/// <summary>Draws indexed hexagonal prism using alternative built in method included. Does not support scale factoring yet</summary>
	/// <param name="sf">Nonfunctional</param>
	void DrawIndexedHexagonalPrismAlt(float sf = 1.0f);


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
	static Vertex cube_vertices[];
	static Color cube_colors[];

	/// <summary>Less memory footprint than previous versions, uses indices</summary>
	static Vertex cube_indexedVertices[];
	static Color cube_indexedColors[];
	static GLushort cube_indices[];

	/// <summary>Similar to the way draw indexedcube handles drawing, only for hexagonal prism</summary>
	static Vertex hexagonalPrism_indexedVertices[];
	static Color hexagonalPrism_indexedColors[];
	static GLushort hexagonalPrism_indices[];

	MouseButtons _mouseButtonPressed = none;
};