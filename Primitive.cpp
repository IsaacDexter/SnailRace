#include "Primitive.h"

//Vertexes cannot be included as they cannot be virtual. Vertexes and drawing code is unique to each child class.

Primitive::Primitive()
{
	m_rotationAxes = new Vector3();
}

Primitive::~Primitive()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
}

void Primitive::Update()
{
	UpdateRotation();
}

/// <summary>Uses the 'DrawIndexed___Alt method as set out in older variations of the code. The most line and memory efficient.</summary>
void Primitive::Draw()
{
	//Leave blank as virtual so will be overriden
}

Vector3* Primitive::GetRotation()
{
	return(m_rotationAxes);
}

void Primitive::SetRotation(Vector3* newRotation)
{
	m_rotationAxes = newRotation;
}

/// <summary>Rotates the shape during the update.</summary>
/// <param name="_rotationAxes"> The _rotationAxes is a vector 3 representing how much to rotate the shape by in each axis.</param>
void Primitive::UpdateRotation()
{
	glRotatef(m_rotationAxes->x, -1.0f, 0.0f, 0.0f);	//Rotate in the x by the x rotation
	glRotatef(m_rotationAxes->y, 0.0f, -1.0f, 0.0f);	//Rotate in the y by the y rotation
	glRotatef(m_rotationAxes->z, 0.0f, 0.0f, -1.0f);	//Rotate in the z by the z rotation
}