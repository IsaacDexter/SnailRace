#include "Primitive.h"

Primitive::Primitive(Mesh* mesh, Texture2D* texture, Material* material, float x, float y, float z)
{
	m_mesh = mesh;
	m_texture = texture;
	m_material = material;
	m_rotationAxes = new Vector3();
	m_position = new Vector3();
	SetPosition(x, y, z);
}

Primitive::~Primitive()
{
	delete m_rotationAxes;
	m_rotationAxes = nullptr;
	delete m_position;
	m_position = nullptr;
}

void Primitive::Update()
{
	UpdatePosition();
	UpdateRotation();
}

/// <summary>Uses the 'DrawIndexed___Alt method as set out in older variations of the code. The most line and memory efficient.</summary>
void Primitive::Draw()
{
	if (m_mesh != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->GetID());	//Bind the texture.
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normals);

		glPushMatrix();

		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

Vector3* Primitive::GetRotation()
{
	return(m_rotationAxes);
}

void Primitive::SetRotation(float pitch, float yaw, float roll)
{
	m_rotationAxes->x = pitch;
	m_rotationAxes->y = yaw;
	m_rotationAxes->z = roll;
}

/// <summary>Rotates the shape during the update.</summary>
/// <param name="_rotationAxes"> The _rotationAxes is a vector 3 representing how much to rotate the shape by in each axis.</param>
void Primitive::UpdateRotation()
{
	glRotatef(m_rotationAxes->x, -1.0f, 0.0f, 0.0f);	//Rotate in the x by the x rotation
	glRotatef(m_rotationAxes->y, 0.0f, -1.0f, 0.0f);	//Rotate in the y by the y rotation
	glRotatef(m_rotationAxes->z, 0.0f, 0.0f, -1.0f);	//Rotate in the z by the z rotation
}

Vector3* Primitive::GetPosition()
{
	return(m_position);
}

void Primitive::SetPosition(float x, float y, float z)
{
	m_position->x = x;
	m_position->y = y;
	m_position->z = z;
}

void Primitive::UpdatePosition()
{
	glTranslatef(m_position->x, m_position->y, m_position->z);
}
