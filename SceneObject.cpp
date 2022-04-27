#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture, Material* material, float x, float y, float z) : Primitive(mesh, texture, material, x, y, z)
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::Draw()
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
		for (int i = 0; i < m_mesh->Indices.size() ; i++)
		{
			glVertex3f(m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).x, m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).y, m_mesh->Vertices.at(m_mesh->Indices.at(i).Vertex - 1).z);
			glTexCoord2f(m_mesh->TexCoords.at(m_mesh->Indices.at(i).TexCoord - 1).u, m_mesh->TexCoords.at(m_mesh->Indices.at(i).TexCoord - 1).v);
			glNormal3f(m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).x, m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).y, m_mesh->Normals.at(m_mesh->Indices.at(i).Normal - 1).z);
		}
		glEnd();

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}
