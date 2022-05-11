#include "Snail.h"

Snail::Snail(Mesh* mesh, Texture2D* texture, Material* material, Vector3 startPos, Vector3 endPos, float speed) : Primitive(mesh, texture, material, startPos)
{
	m_speed = speed;
	m_endPos = endPos;
	m_finished = false;
}

Snail::~Snail()
{
}

void Snail::Update()
{
	if (!m_finished)
	{
		m_position->x += m_speed / 1000;
		if (m_position->x > m_endPos.x)
		{
			m_finished = true;
		}
	}
}

bool Snail::GetFinished()
{
	return m_finished;
}

