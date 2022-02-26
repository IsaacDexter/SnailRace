#ifndef _HEXAGONAL_PRISM_H
#define _HEXAGONAL_PRISM_H

#include "Primitive.h"
#include "Structures.h"

class HexagonalPrism : public Primitive
{
public:
	HexagonalPrism(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~HexagonalPrism();
};

#endif // !_HEXAGONAL_PRISM_H