#include "Snail.h"
#include "Structures.h"

/// <summary>The snail differs from primitive through its ability to race in the positive x, through its update functions.</summary>
/// <param name="mesh">The mesh to use (g_snailMesh)</param>
/// <param name="texture">The texture to use</param>
/// <param name="material">The material to use</param>
/// <param name="startPos">The starting line</param>
/// <param name="endPos">the finishing line</param>
Snail::Snail(Mesh* mesh, Texture2D* texture, Material* material, Vector3 startPos, Vector3 endPos) : Primitive(mesh, texture, material, startPos)
{
	m_speed = 0.0f;
	m_endPos = endPos;
	m_finished = false;
}

Snail::~Snail()
{
}

/// <summary>If the snail isnt finished, reroll its speed, move it forward in the positive x by the speed * the refreshrate, and check to see if its hit the finishline.</summary>
void Snail::Update()
{
	if (!m_finished)
	{
		srand(m_position->x + m_position->z + m_speed);
		m_speed = rand() % 30;
		m_position->x +=( m_speed / 500);
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

/// <summary>Randomise m_speed by the current time.</summary>
void Snail::RollSpeed()
{
	srand(time(NULL));
	m_speed = rand() % 30;
}

