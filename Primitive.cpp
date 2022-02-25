#include "Primitive.h"

//Vertexes cannot be included as they cannot be virtual. Vertexes and drawing code is unique to each child class.

Primitive::Primitive()
{
	
}

Primitive::~Primitive()
{

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
	//Leave blank as virtual so will be overriden
}