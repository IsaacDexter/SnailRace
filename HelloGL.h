#pragma once
#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include "GLUTCallbacks.h"

class HelloGL
{
public:
	//Constructor def
	HelloGL(int argc, char* argv[]);

	//Destructor def
	~HelloGL(void);

	//Display method
	void Display();
};