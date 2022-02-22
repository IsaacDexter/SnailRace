#include "Primitive.h"

/// <summary>All 8 indexed vertices in the cube</summary>
Vertex Primitive::indexedVertices[] = {
	 1, 1, 1,	//vertex 0
	-1, 1, 1,	//vertex 1
	-1,-1, 1,	//vertex 2
	 1,-1, 1,	//vertex 3
	 1,-1,-1,	//vertex 4
	 1, 1,-1,	//vertex 5
	-1, 1,-1,	//vertex 6
	-1,-1,-1	//vertex 7
};	//8 vertices

/// <summary>The color associated with each vertex</summary>
Color Primitive::indexedColors[] = {
	 1, 1, 1,	//vertex 0, white
	 0, 1, 1,	//vertex 1, cyan
	 0, 0, 1,	//vertex 2, blue
	 1, 0, 1,	//vertex 3, magenta
	 1, 0, 0,	//vertex 4, red
	 1, 1, 0,	//vertex 5, yellow
	 0, 1, 0,	//vertex 6, green
	 0, 0, 0	//vertex 7, black
};	//8 colours

/// <summary>Defines the triangles that make up the Cube, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
GLushort Primitive::indices[] = {
	0,	1,	2,		2,	3,	0,	//Front
	0,	3,	4,		4,	5,	0,	//Right
	0,	5,	6,		6,	1,	0,	//Top
	1,	6,	7,		7,	2,	1,	//Left
	7,	4,	3,		3,	2,	7,	//Bottom
	4,	7,	6,		6,	5,	4	//Back
};	//12 triangles, 36 vertices overall

Primitive::Primitive()
{
}

void Primitive::Update(Vector3* _rotationAxes)
{
	glRotatef(_rotationAxes->x, -1.0f, 0.0f, 0.0f);	//Rotate in the x by the x rotation
	glRotatef(_rotationAxes->y, 0.0f, -1.0f, 0.0f);	//Rotate in the y by the y rotation
	glRotatef(_rotationAxes->z, 0.0f, 0.0f, -1.0f);	//Rotate in the z by the z rotation
}

void Primitive::Draw()
{
	
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();

	glDrawElements(GL_TRIANGLES, numberOfTriangles, GL_UNSIGNED_SHORT, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}