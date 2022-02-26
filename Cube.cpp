#include "Cube.h"

Cube::Cube(float x, float y, float z) : Primitive(x, y, z)
{
}

Cube::~Cube()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}