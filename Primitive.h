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
protected:
	///<summary>All indexed vertices in the shape</summary>
	static Vertex indexedVertices[];
	/// <summary>The color associated with each vertex</summary>
	static Color indexedColors[];
	/// <summary>Defines the triangles that make up the shape, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
	static GLushort indices[];
	
	/// <summary>The number of vertices. Generated automatically with the NUM macro</summary>
	GLushort m_numberOfVertices;
	/// <summary>The rotation of the shape, stored as an x, y and z value.</summary>
	Vector3* m_rotationAxes;
public:
	/// <summary>Constructor. Sets m_numberOfTriangles in subclasses</summary>
	Primitive();
	~Primitive();

	/// <summary>Getter for the rotation</summary>
	/// <returns>The Rotation</returns>
	Vector3* GetRotation();
	/// <summary>Setter for the rotation</summary>
	/// <param name="newRotation">the new rotation</param>
	void SetRotation(Vector3* newRotation);

	/// <summary>Kept blank as needs replacing in child classes. As a result of a non-thorough understanding of classes</summary>
	virtual void Draw();
	/// <summary>Updates the shape, namely the rotation with the axes given.</summary>
	void Update(Vector3* _rotationAxes);
};

#endif // !_PRIMITIVE_H