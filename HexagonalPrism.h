#ifndef _HEXAGONAL_PRISM_H
#define _HEXAGONAL_PRISM_H

#include "Primitive.h"
#include "Structures.h"

class HexagonalPrism : public Primitive
{
protected:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
public:
	HexagonalPrism();
	~HexagonalPrism();

	void Draw() override;
};

#endif // !_HEXAGONAL_PRISM_H