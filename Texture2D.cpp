#include "Texture2D.h"

#include <fstream>
#include <iostream>
using namespace std;

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures();
}

bool Texture2D::Load(char* path, int width, int height)
{
	return false;
}

GLuint Texture2D::GetID() const
{
	return m_ID;
}

int Texture2D::GetWidth() const
{
	return m_width;
}

int Texture2D::GetHeight() const
{
	return m_height;
}
