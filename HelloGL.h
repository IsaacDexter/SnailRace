#pragma once
#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include "GLUTCallbacks.h"


/// <summary>
/// Simple enum used to store different triangle types.
/// </summary>
enum TriangleTypes
{
	Scalene = 1,
	Isoceles,
	Equilateral,
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
};