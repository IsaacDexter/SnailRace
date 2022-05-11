#include "String2D.h"
#include "Camera.h"

String2D::String2D(std::string text, Vector3 position, Color color, Camera* camera)
{
	m_position = new Vector3(position.x, position.y, position.z);
	m_color = new Color(color.r, color.g, color.b);
	m_text = text;
	m_camera = camera;
}

String2D::~String2D()
{
	delete m_position;
	m_position = nullptr;
	delete m_color;
	m_color = nullptr;
}

void String2D::Update()
{
	m_position->x = m_camera->getViewport().x;
	m_position->y = m_camera->getViewport().y;
	m_position->z = m_camera->getViewport().z;
}

void String2D::Draw()
{
	glDisable(GL_LIGHTING);
	glTranslatef(m_position->x, m_position->y, m_position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)m_text.c_str());
	glEnable(GL_LIGHTING);
}

void String2D::SetText(std::string text)
{
	m_text = text;
}

std::string String2D::GetText()
{
	return m_text;
}
