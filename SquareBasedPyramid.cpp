#include "SquareBasedPyramid.h"

SquareBasedPyramid::SquareBasedPyramid(float x, float y, float z) : Primitive(x, y, z)
{
}

SquareBasedPyramid::~SquareBasedPyramid()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}
