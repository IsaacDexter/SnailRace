#include "HexagonalPrism.h"

HexagonalPrism::HexagonalPrism(float x, float y, float z) : Primitive(x, y, z)
{
}

HexagonalPrism::~HexagonalPrism()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}
