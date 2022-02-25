#include "SquareBasedPyramid.h"

Vertex SquareBasedPyramid::indexedVertices[] = {
	 0,	 1,	 0,	//vertex 0 (Point)
	 1,	-1,	 1,	//vertex 1
	-1,	-1,	 1,	//vertex 2
	-1,	-1,	-1,	//vertex 3
	 1,	-1,	-1,	//vertex 4
};	//5 vertices

Color SquareBasedPyramid::indexedColors[] = {
	1,	1,	1,	//white, point
	1,	0,	0,	//red
	0,	0,	1,	//blue
	1,	1,	0,	//yellow
	0,	1,	0	//green
};	//5 colors

GLushort SquareBasedPyramid::indices[] = {
	2,	1,	0,	//face 1
	3,	2,	0,	//face 2
	4,	3,	0,	//face 3
	1,	4,	0,	//face 4
	2,	3,	1,	//base 1
	4,	1,	3,	//base 2
};	//6 triangles,	18 vertices overall.

SquareBasedPyramid::SquareBasedPyramid()
{
	m_rotationAxes = new Vector3();
	m_numberOfVertices = NUM(indices);
}

SquareBasedPyramid::~SquareBasedPyramid()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}

void SquareBasedPyramid::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();

	glDrawElements(GL_TRIANGLES, m_numberOfVertices, GL_UNSIGNED_SHORT, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
