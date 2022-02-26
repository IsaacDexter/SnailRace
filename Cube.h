#ifndef _CUBE_H
#define _CUBE_H

#include "Primitive.h"
#include "Structures.h"

class Cube : public Primitive
{
protected:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
public:
	Cube(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Cube();

	void Draw() override;
};

#endif // !_CUBE_H