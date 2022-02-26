#ifndef _SQUARE_BASED_PYRAMID_H
#define _SQUARE_BASED_PYRAMID_H

#include "Primitive.h"
#include "Structures.h"

class SquareBasedPyramid : public Primitive
{
protected:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
public:
	SquareBasedPyramid(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~SquareBasedPyramid();

	void Draw() override;
};

#endif // !_SQUARE_BASED_PYRAMID_H