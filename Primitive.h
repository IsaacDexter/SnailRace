#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

//includes
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <fstream>
#include <iostream>
#include <string>



class Primitive
{
protected:
	//Static variables only exist once in memory over every instance of the object we make.

	Mesh* m_mesh;

	/// <summary>The rotation of the shape, stored as an pitch, yaw and roll value.</summary>
	Vector3* m_rotationAxes;
	/// <summary>The position of the shape, stored as an x, y and z value.</summary>
	Vector3* m_position;
public:
	/// <summary>Constructor. Sets m_numberOfTriangles in subclasses, as well as rotation and position. Takes the starting position as params.</summary>
	Primitive(Mesh* mesh, float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Primitive();

	/// <summary>Load method which loads data into the num variables and m_ind variables.</summary>
	/// <param name="path">Path to the .txt file to load the object from. Should Start with Models/_____</param>
	/// <returns>Whether the load was a success.</returns>
	//static bool Load(char* path);

	/// <summary>Getter for the rotation</summary>
	/// <returns>The Rotation</returns>
	Vector3* GetRotation();
	/// <summary>Setter for the rotation</summary>
	/// <param name="pitch, yaw, roll">the new rotation as pitch yaw roll</param>
	void SetRotation(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f);
	/// <summary> Translates the rotation of the shape to be up to date with m_rotationAxes</summary>
	void UpdateRotation();

	/// <summary>Getter for the Position</summary>
	/// <returns>The Position</returns>
	Vector3* GetPosition();
	/// <summary>Setter for the Position</summary>
	/// <param name="newRotation">the new Position</param>
	void SetPosition(float x, float y, float z);
	/// <summary> Translates the Position of the shape to be up to date with m_position</summary>
	void UpdatePosition();

	/// <summary>Kept blank as needs replacing in child classes. As a result of a non-thorough understanding of classes</summary>
	virtual void Draw();
	/// <summary>Updates the shape, namely the rotation with the m_rotationAxes variable.</summary>
	void Update();
};

#endif // !_PRIMITIVE_H