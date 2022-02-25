#include "HexagonalPrism.h"

Vertex HexagonalPrism::indexedVertices[] = {
	//Front Face
	-1,0,1,			//vertex 0
	-0.5,0.866,1,	//vertex 1
	0.5,0.866,1,	//vertex 2
	1,0,1,			//vertex 3
	0.5,-0.866,1,	//vertex 4
	-0.5,-0.866,1,	//vertex 5

	//Back Face
	-1,0,-1,		//vertex 6
	-0.5,0.866,-1,	//vertex 7
	0.5,0.866,-1,	//vertex 8
	1,0,-1,			//vertex 9
	0.5,-0.866,-1,	//vertex 10
	-0.5,-0.866,-1	//vertex 11
};	//12 Vertices

Color HexagonalPrism::indexedColors[] = {
	1,		0,		0,		//red
	1,		0.25,	0,
	1,		0.5,	0.25,
	1,		0.5,	0.5,	//pink
	1,		0.25,	0.5,
	1,		0,		0.25,


	0.5,	0.5,	1,		//pale blue
	0.5,	0.25,	1,
	0.25,	0,		1,
	0,		0,		1,		//blue
	0,		0.25,	1,
	0.25,	0.5,	1
};	//12 colours

GLushort HexagonalPrism::indices[] = {
	2,	1,	0,		0,	5,	4,		4,	3,	2,		2,	0,	4,	//Front Face
	9,	10,	11,		11,	6,	7,			7,	8,	9,		9,	11,	7,	//Rear Face
	1,	2,	8,		8,	7,	1,	//top side
	2,	3,	9,		9,	8,	2,	//top right side
	3,	4,	10,		10,	9,	3,	//bottom right side
	4,	5,	11,		11,	10,	4,	//bottom side
	5,	0,	6,		6,	11,	5,	//bottom left side
	0,	1,	7,		7,	6,	0	//top left side
};	//20 triangles, 60 vertices overall

HexagonalPrism::HexagonalPrism()
{
	m_rotationAxes = new Vector3();
	m_numberOfVertices = NUM(indices);
}

HexagonalPrism::~HexagonalPrism()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}

void HexagonalPrism::Draw()
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
