#ifndef _HELLOGL_H
#define _HELLOGL_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Enums.h"

//Shape class includes
#include "Primitive.h"
#include "SceneObject.h"
#include "MeshLoader.h"

//Text includes
#include "String2D.h"

//Linked List includes
#include "LinkedLists.h"


//Defs
#define REFRESHRATE 16
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800



class HelloGL
{
public:
	//Constructor def
	HelloGL(int argc, char* argv[]);
	//Initialisation methods
	void InitObjects();
	void InitLighting(Vector3 lightPosition, Vector4 ambient, Vector4 diffuse, Vector4 specular);
	void InitMaterials();
	void InitGL(int argc, char* argv[]);

	//Destructor def
	~HelloGL(void);

	//Display methods
	///<summary></summary>
	void Display();

	//Input Methods
	void Keyboard(unsigned char key, int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void PassiveMouseMotion(int x, int y);

	//Update methods
	void Update();
private:
	/// <summary>1 for center, 2 for eye, 3 for up</summary>
	int g_viewMode = 1;
	Camera* g_camera;
	/// <summary>Vector2 storing mouse position</summary>
	Vector2* g_oldMousePos;
	/// <summary>Vector3 representing the rotation in each axis</summary>
	Vector3* g_rotationAxes;

	Vector4* g_lightPosition;
	Lighting* g_lightData;

	//Meshes
	Mesh* g_cubeMesh;
	Mesh* g_hexagonalPrismMesh;

	//Textures
	Texture2D* g_brickTexture;
	Texture2D* g_penguinTexture;

	//Materials
	Material* g_brickMaterial;
	Material* g_penguinMaterial;

	//Text
	String2D* g_string;

	//List containing 3D shapes
	LinkedLists* g_sceneObjectsList;
	ListNode* g_head;
	SceneObject* g_cube;

	MouseButtons g_mouseButtonPressed = none;
	int g_currentSceneObjectLocation;
};



#endif // !_HELLOGL_H