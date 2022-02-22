#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

//includes
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"



class Primitive
{
private:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
public:
	Primitive();
	~Primitive();

	GLushort numberOfTriangles = 36;

	void Draw();
	void Update(Vector3* _rotationAxes);
};

#endif // !_PRIMITIVE_H