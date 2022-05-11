#ifndef _STRING_2D_H
#define _STRING_2D_H

#include "Structures.h"
#include <string>

class Camera;

class String2D
{
public:
	String2D(std::string text, Vector3 position, Color color, Camera* camera);
	~String2D();

	void Update();

	void Draw();
	void SetText(std::string text);
	std::string GetText();

private:
	std::string m_text;
	Vector3* m_position;
	Color* m_color;
	Camera* m_camera;
};


#endif // !_STRING_2D_H