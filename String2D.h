#ifndef _STRING_2D_H
#define _STRING_2D_H

#include "Structures.h"

class String2D
{
private:
	char* m_text;
	Vector3* m_position;
	Vector2* m_rasterPosition;
	Color* m_color;
public:
	String2D(char* text, Vector3 m_position, Color m_color, Vector2 rasterPosition = Vector2());
	~String2D();
	void Draw();
};

#endif // !_STRING_2D_H