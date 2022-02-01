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

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}
}