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

	//Input Methods
	void Keyboard(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);

	//Update methods
	void Update();
private:
	/// <summary>1 for center, 2 for eye, 3 for up</summary>
	int viewMode = 1;
	float _rectangleRotation;
	Camera* camera;
	Vector2* _oldMousePos;
};