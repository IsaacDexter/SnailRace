#ifndef _SQUARE_BASED_PYRAMID_H
#define _SQUARE_BASED_PYRAMID_H

#include "Primitive.h"
#include "Structures.h"

class SquareBasedPyramid : public Primitive
{
protected:
public:
	SquareBasedPyramid(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~SquareBasedPyramid();
};

#endif // !_SQUARE_BASED_PYRAMID_H