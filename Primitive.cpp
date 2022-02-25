#include "Primitive.h"

/// <summary>All indexed vertices in the shape</summary>
Vertex Primitive::indexedVertices[] = {

};	//n vertices

/// <summary>The color associated with each vertex</summary>
Color Primitive::indexedColors[] = {

};	//n colours

/// <summary>Defines the triangles that make up the shape, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
GLushort Primitive::indices[] = {

};	//m triangles, m*3 vertices overall

Primitive::Primitive()
{
	//Calculates the number of triangles using the num macro. Used in the draw function
	m_numberOfTriangles = NUM(indices);
}

/// <summary>Rotates the shape during the update.</summary>
/// <param name="_rotationAxes"> The _rotationAxes is a vector 3 representing how much to rotate the shape by in each axis.</param>
void Primitive::Update(Vector3* _rotationAxes)
{
	glRotatef(_rotationAxes->x, -1.0f, 0.0f, 0.0f);	//Rotate in the x by the x rotation
	glRotatef(_rotationAxes->y, 0.0f, -1.0f, 0.0f);	//Rotate in the y by the y rotation
	glRotatef(_rotationAxes->z, 0.0f, 0.0f, -1.0f);	//Rotate in the z by the z rotation
}

/// <summary>Uses the 'DrawIndexed___Alt method as set out in older variations of the code. The most line and memory efficient.</summary>
void Primitive::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();

	glDrawElements(GL_TRIANGLES, m_numberOfTriangles, GL_UNSIGNED_SHORT, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}