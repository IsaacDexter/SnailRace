#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library
#include <vector>

class Primitive;

#define pi 3.14159265358979323846
//Macro used to find the number of elements in a list.
#define NUM(a) (sizeof(a) / sizeof(*a))
#define RADIANS(a) (a * pi/180)

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
		w = 1.0f;
	}
	/// <summary>Vector 4 allowing us to represent our data as Homogeneous Coordinates, which we need to perform transformations correctly as a fourth component is required for matrix mulitplications.</summary>
	/// <param name="initial_x">The initial x value. Defaults to 0.0f</param>
	/// <param name="initial_y">The initial y value. Defaults to 0.0f</param>
	/// <param name="initial_z">The initial z value. Defaults to 0.0f</param>
	/// <param name="initial_w">The initial w value, used in calculations. Defaults to 1.0f</param>
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
	/// <summary>A 3D vector represeting a single point in space.</summary>
	/// <param name="initial_x">The initial x value. Defaults to 0.0f</param>
	/// <param name="initial_y">The initial y value. Defaults to 0.0f</param>
	/// <param name="initial_z">The initial z value. Defaults to 0.0f</param>
	Vector3(float initial_x, float initial_y, float initial_z)
	{
		x = initial_x;
		y = initial_y;
		z = initial_z;
	}
};

/// <summary>A 3D vector represeting an RGB color</summary>
struct Color
{
	float r;
	float g;
	float b;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}
	/// <summary>A 3D vector represeting an RGB color.</summary>
	/// <param name="initial_x">The initial r value. Defaults to 0.0f</param>
	/// <param name="initial_y">The initial g value. Defaults to 0.0f</param>
	/// <param name="initial_z">The initial b value. Defaults to 0.0f</param>
	Color(float initial_r, float initial_g, float initial_b)
	{
		r = initial_r / 255.0f;
		g = initial_g / 255.0f;
		b = initial_b / 255.0f;
	}
};

/// <summary>A matrix 4. essentially a glm::mat4</summary>
struct Matrix4
{
	float m[4][4];

	Matrix4()
	{
		float m[4][4];
	}

	/// <summary>A 4 dimensional matrix. essentially a glm::mat4</summary>
	/// <param name="initialFloat">what to set the matrix to initially. leave blank for undefined.</param>
	Matrix4(float initialFloat)
	{
		float m[4][4];
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				m[y][x] = initialFloat;
			}
		}
	}
};

//typedef float Matrix4[4][4];

/// <summary>A vector 2 representing a single point in 2D space.</summary>
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
	/// <summary>A vector 2 representing a single point in 2D space.</summary>
	/// <param name="initial_x">The initial x value. Defaults to 0.0f</param>
	/// <param name="initial_y">The initial y value. Defaults to 0.0f</param>
	Vector2(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

/// <summary>Used to store vertexes in a 3D shape. uses GLfloat to avoid compiler warnings</summary>
struct Vertex
{
	GLfloat x, y, z;
};

/// <summary>
/// A texutre coordinate, with a u and v value. Used in loading textures from files.
/// </summary>
struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

struct Index
{
	GLushort Vertex;
	GLushort TexCoord;
	GLushort Normal;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Index()
	{
		Vertex = 1;
		TexCoord = 1;
		Normal = 1;
	}
	/// <summary>An Index representing a vertex index, a texcoord index and a normal index</summary>
	/// <param name="initial_Vertex">The vertex index. Defaults to 1</param>
	/// <param name="initial_TexCoord">The texcoord(uv) index. Defaults to 1</param>
	/// <param name="initial_Normal">The normal index. Defaults to 1</param>
	Index(GLushort initial_Vertex, GLushort initial_TexCoord, GLushort initial_Normal)
	{
		Vertex = initial_Vertex;
		TexCoord = initial_TexCoord;
		Normal = initial_Normal;
	}
};
/// <summary>
/// Structure used to load 3D shapes, contains each vertex, normals and a lkist of indeces. Also contains texturing coords.
/// </summary>
struct Mesh
{
	///<summary>All indexed vertices in the shape</summary>
	std::vector<Vertex> Vertices;
	/// <summary>The coordinates of the texture to be loaded onto the mesh</summary>
	std::vector<TexCoord> TexCoords;
	/// <summary>The Normals, which are used in giving a shape the illusion of texture. Can either be calculated automatically or loaded from a file.</summary>
	std::vector<Vector3> Normals;
	/// <summary>Defines the triangles that make up the shape, using the indices of each of the vertices/colors.  GLuShort is an in built typedef of 16 bit unsigned binary integer.</summary>
	std::vector<Index> Indices;
};

/// <summary>Vector containing the required components for lighting</summary>
struct Lighting
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

/// <summary>Contains required components for calculating how light interacts with a surface.</summary>
struct Material
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Shininess;
	//Defines default constructiors, to allows to create an object of this type in function calls.
	Material()
	{
		Ambient = Vector4();
		Diffuse = Vector4();
		Specular = Vector4();
		Shininess = 0.0f;
	}
	/// <summary>A Material, representing a textured surface. Determines how light interacts with a surface. All variables will default to 0.0f unless otherwise stated.</summary>
	/// <param name="initial_ambient">The ambient, as a vector4, representing the r, g, b and w. Advise setting w to 1.0f for all. The ambient represents uniform colour, resulting in a matte object.</param>
	/// <param name="initial_diffuse">The diffuse as a v4, repping the rgb and w, which should most likely be set to 1.0f. Diffuse represents how photons will bounce off of the surface, (which colour lights will be absorbed).</param>
	/// <param name="initial_specular">The diffuse as a v4, repping the rgb and w, which should most likely be set to 1.0f. Specular lighting is considering direct reflection. This affects a highlight and makes it shinier and more 'finished'.</param>
	/// <param name="initial_shininess">How matte, or course, the object apperars. The more shine, the more polished it will apear.</param>
	Material(Vector4 initial_ambient, Vector4 initial_diffuse, Vector4 initial_specular, GLfloat initial_shininess)
	{
		Ambient = initial_ambient;
		Diffuse = initial_diffuse;
		Specular = initial_specular;
		Shininess = initial_shininess;
	}
};

/// <summary>Used in linked lists, containing a scene object pointer, and the next node in the linked lists. Allows for a dynamic collection of objects that can be added to/ removed from at runtim,e.</summary>
struct ListNode
{
	Primitive* sceneObject;
	ListNode* next;
};

#endif // !_STRUCTURES_H
