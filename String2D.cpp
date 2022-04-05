#include "String2D.h"

/// <summary>String 2D object represents a 2D string in 3D space</summary>
/// <param name="text">The text to display</param>
/// <param name="position">position of the string in 3d space</param>
/// <param name="color">Color of the string</param>
/// <param name="rasterPosition">Raster positon (opitional)</param>
String2D::String2D(char* text, Vector3 position, Color color, Vector2 rasterPosition)
{
	m_text = text;
	m_position = new Vector3(position);
	m_color = new Color(color);
	m_rasterPosition = new Vector2(rasterPosition);
}

String2D::~String2D()
{
	delete m_position;
	m_position = nullptr;
	delete m_position;
	m_position = nullptr;
	delete m_position;
	m_position = nullptr;
	delete m_position;
	m_position = nullptr;
}

void String2D::Draw()
{
	glPushMatrix();

	glColor3f(m_color->r, m_color->g, m_color->b);
	glTranslatef(m_position->x, m_position->y, m_position->z);
	glRasterPos2f(m_rasterPosition->x, m_rasterPosition->y);	//The raster position on the screen which we manupulate with the translate
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)m_text);	//Thakes the font type and the string to display

	glPopMatrix();
}
