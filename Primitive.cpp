#include "Primitive.h"

Primitive::Primitive(Mesh* mesh, Texture2D* texture, Material* material, Vector3 startPos)
{
	m_mesh = mesh;
	m_texture = texture;
	m_material = material;
	m_rotationAxes = new Vector3();
	m_position = new Vector3(startPos);
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
	//UpdatePosition();
	//UpdateRotation();
}

void Primitive::DrawMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(m_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(m_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(m_material->Specular.x));
	glMaterialfv(GL_FRONT, GL_SHININESS, &(m_material->Shininess));
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

		DrawMaterial();

		glPushMatrix();

		UpdatePosition();
		UpdateRotation();
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_mesh->Indices.size(); i++)
		{

			glTexCoord2f(m_mesh->TexCoords.at(m_mesh->Indices.at(i).TexCoord - 1).u, m_mesh->TexCoords.at(m_mesh->Indices.at(i).TexCoord - 1).v);
			glNormal3f(m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).x, m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).y, m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).z);
			glVertex3f(m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).x, m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).y, m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).z);
		}
		glEnd();

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
