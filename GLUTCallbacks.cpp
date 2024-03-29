#include "GLUTCallbacks.h"
#include "HelloGL.h"

//namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		//intitalise a null pointer before we do anything
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}

	void MouseMotion(int x, int y)
	{
		helloGL->MouseMotion(x, y);
	}

	void PassiveMouseMotion(int x, int y)
	{
		helloGL->PassiveMouseMotion(x, y);
	}

	void MouseButton(int button, int state, int x, int y)
	{
		helloGL->MouseButton(button, state, x, y);
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		//Calls the update function
		helloGL->Update();
		//Sets a new timer for the same FPS. not hardcoded in case it changes during the program. Calls itself in turn, effectively updating the program every 16ms for perpetua.
		glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
	}
}