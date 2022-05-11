#ifndef _HELLOGL_H
#define _HELLOGL_H

#include <Windows.h>		//Required for OpenGl on Windows
#include <gl/GL.h>			//OpenGL
#include <gl/GLU.h>			//OpenGL Utilities
#include "GL/freeglut.h"	//freeGLUT library

#include <ft2build.h>	//Freetype library
#include FT_FREETYPE_H	//Freetyoe macro fo instalation specific macros


#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Enums.h"

//Shape class includes
#include "Primitive.h"
#include "MeshLoader.h"

//Math Includes
#include "Math.h"

////Text includes
//#include "String2D.h"

//Linked List includes
#include "LinkedLists.h"


//Defs
#define REFRESHRATE 1000/60
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

class Camera;


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
	/// <summary>The 3D camera, containing a position, a target, used to get the direction, a right axis and an up axis.</summary>
	Camera* g_camera;
	/// <summary>Vector2 storing mouse position</summary>
	Vector2* g_oldMousePos;
	/// <summary>Used to stop initial jump of the mouse</summary>
	bool firstMouse = true;
	/// <summary>Vector3 representing the rotation in each axis</summary>
	Vector3* g_rotationAxes;

	Vector4* g_lightPosition;
	Lighting* g_lightData;

	//Meshes
	Mesh* g_cubeMesh;
	Mesh* g_hexagonalPrismMesh;
	Mesh* g_skyboxMesh;
	Mesh* g_snailMesh;

	//Textures
	Texture2D* g_brickTexture;
	Texture2D* g_penguinTexture;
	Texture2D* g_skyboxTexture;

	//Materials
	Material* g_brickMaterial;
	Material* g_penguinMaterial;
	Material* g_skyboxMaterial;

	//Text
	//String2D* g_string;
	FT_Library g_freetypeLibrary;

	//List containing 3D shapes
	LinkedLists* g_sceneObjectsList;
	ListNode* g_head;
	Primitive* g_skybox;

	MouseButtons g_mouseButtonPressed = none;
	int g_currentSceneObjectLocation;
};



#endif // !_HELLOGL_H