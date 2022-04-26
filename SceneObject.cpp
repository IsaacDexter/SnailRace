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

		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normals);

		DrawMaterial();

		glPushMatrix();

		UpdatePosition();
		UpdateRotation();
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_mesh->IndexCount; i++)
		{
			glVertex3f(m_mesh->Vertices[m_mesh->ObjIndices[i].vertex - 1].x, m_mesh->Vertices[m_mesh->ObjIndices[i].vertex - 1].y, m_mesh->Vertices[m_mesh->ObjIndices[i].vertex - 1].z);
			glTexCoord2f(m_mesh->TexCoords[m_mesh->ObjIndices[i].uv - 1].u, m_mesh->TexCoords[m_mesh->ObjIndices[i].uv - 1].v);
			glNormal3f(m_mesh->Normals[m_mesh->ObjIndices[i].normal - 1].x, m_mesh->Normals[m_mesh->ObjIndices[i].normal - 1].y, m_mesh->Normals[m_mesh->ObjIndices[i].normal - 1].z);
		}
		glEnd();

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}
