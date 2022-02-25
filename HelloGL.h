#ifndef _HELLOGL_H
#define _HELLOGL_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Enums.h"
#include "Primitive.h"


//Defs
#define REFRESHRATE 16
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800



class HelloGL
{
public:
	//Constructor def
	HelloGL(int argc, char* argv[]);


	//Destructor def
	~HelloGL(void);

	//Display methods
	///<summary></summary>
	void Display();

	void DrawCubeArrayAlt(float sf = 1.0f);
	/// <summary>The most memory and line efficient of the 3 methods. Uses indexed vertices and colors, as well as an indices array</summary>
	/// <param name="sf">The scale factor. Defaults to 0.1</param>

	/// <summary>Draws indexed hexagonal prism using alternative built in method included. Does not support scale factoring yet</summary>
	/// <param name="sf">Nonfunctional</param>
	void DrawIndexedHexagonalPrismAlt(float sf = 1.0f);

	/// <summary>Draws indexed square based pyramid using alternative built in method included. Does not support scale factoring yet</summary>
	/// <param name="sf">Nonfunctional</param>
	void DrawIndexedSquareBasedPyramidAlt(float sf = 1.0f);

	//Input Methods
	void Keyboard(unsigned char key, int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void PassiveMouseMotion(int x, int y);

	//Update methods
	void Update();
private:
	/// <summary>1 for center, 2 for eye, 3 for up</summary>
	int viewMode = 1;
	Camera* camera;
	/// <summary>Vector2 storing mouse position</summary>
	Vector2* _oldMousePos;
	/// <summary>Vector3 representing the rotation in each axis</summary>
	Vector3* _rotationAxes;

	Primitive* _cube;

	/// <summary>Static for now to allow for easy initialisation, but this will most likely be changed when starting to load files</summary>
	static Vertex cube_vertices[];
	static Color cube_colors[];

	/// <summary>Less memory footprint than previous versions, uses indices</summary>
	static Vertex cube_indexedVertices[];
	static Color cube_indexedColors[];
	static GLushort cube_indices[];

	/// <summary>Similar to the way draw indexedcube handles drawing, only for hexagonal prism</summary>
	static Vertex hexagonalPrism_indexedVertices[];
	static Color hexagonalPrism_indexedColors[];
	static GLushort hexagonalPrism_indices[];

	/// <summary>Similar to the way draw indexedcube handles drawing, only for square based pyramid</summary>
	static Vertex squareBasedPyramid_indexedVertices[];
	static Color squareBasedPyramid_indexedColors[];
	static GLushort squareBasedPyramid_indices[];

	MouseButtons _mouseButtonPressed = none;
	Shapes _currentShape = cube;

};



#endif // !_HELLOGL_H