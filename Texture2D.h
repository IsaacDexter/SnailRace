#ifndef _TEXTURE_2D_H
#define _TEXTURE_2D_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

class Texture2D
{
private:
	GLuint m_ID;
	int m_width, m_height;
public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);
	bool LoadBMP(char* path);

	GLuint GetID() const;
	int GetWidth() const;
	int GetHeight() const;
};

#endif // !_TEXTURE_2D_H