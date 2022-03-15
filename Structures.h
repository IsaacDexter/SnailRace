#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

//Macro used to find the number of elements in a list.
#define NUM(a) (sizeof(a) / sizeof(*a))

/// <summary>Vector 4 allowing us to represent our data as Homogeneous Coordinates, which we need to perform transformations correctly as a fourth component is required for matrix mulitplications.</summary>
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
	//Defines default constructors, to allows to create an object of this type in function calls.
	Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	//Allows us to take parameters, so we can construct with any values
	Vector4(float initial_x, float initial_y, float initial_z, float initial_w)
	{
		x = initial_x;
		y = initial_y;
		z = initial_z;
		w = initial_w;
	}
};

/// <summary>A 3D vector represeting a single point in space</summary>
struct Vector3
{
	float x;
	float y;
	float z;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	//Allows us to take parameters, so we can construct with any values
	Vector3(float initial_x, float initial_y, float initial_z)
	{
		x = initial_x;
		y = initial_y;
		z = initial_z;
	}
};

struct Vector2
{
	float x;
	float y;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	//Allows us to take parameters, so we can construct with any values
	Vector2(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

/// <summary>Used to store colours for each vertex in a 3D shape. uses GLfloat to avoid compiler warnings</summary>
struct Color
{
	GLfloat r, g, b;
};

/// <summary>Used to store vertexes in a 3D shape. uses GLfloat to avoid compiler warnings</summary>
struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

/// <summary>
/// Structure used to load 3D shapes, contains each vertex, normals and a lkist of indeces. Also contains texturing coords.
/// </summary>
struct Mesh
{
	///<summary>All indexed vertices in the shape</summary>
	Vertex* Vertices;
	/// <summary>The Normals, which are used in giving a shape the illusion of texture. Can either be calculated automatically or loaded from a file.</summary>
	Vector3* Normals;
	/// <summary>Defines the triangles that make up the shape, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
	GLushort* Indices;
	/// <summary>The coordinates of the texture to be loaded onto the mesh</summary>
	TexCoord* TexCoords;
	//ints used in the loading of files.
	int VertexCount, ColorCount, IndexCount, TexCoordCount;
};

/// <summary>Vector containing the required components for lighting</summary>
struct Lighting
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

struct Material
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Roughness;
};

#endif // !_STRUCTURES_H
