#pragma once
class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);

	void Display();

	void Keyboard(unsigned char key, int x, int y);

	void MouseMotion(int x, int y);

	void PassiveMouseMotion(int x, int y);

	void MouseButton(int button, int state, int x, int y);

	void Timer(int prefferedRefresh);
}