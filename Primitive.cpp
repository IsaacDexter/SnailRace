#include "Primitive.h"

//Vertexes cannot be included as they cannot be virtual. Vertexes and drawing code is unique to each child class.


//initialises loading integers





Primitive::Primitive(Mesh* mesh, float x, float y, float z)
{
	m_mesh = mesh;
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
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, m_mesh->Colors);

		glPushMatrix();

		glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

Vector3* Primitive::GetRotation()
{
	return(m_rotationAxes);
}

//bool Primitive::Load(char* path)
//{
//	std::ifstream inFile;
//	inFile.open(path);
//	if (!inFile.good())
//	{
//		std::cerr << "Can't open text file " << path << std::endl;
//		return false;
//	}
//	
//	inFile >> m_numVertices;
//	m_indexedVertices = new Vertex[m_numVertices];
//	std::string fileValue;
//	for (int i = 0; i < m_numVertices; i++)
//	{
//		inFile >> fileValue;
//		m_indexedVertices[i].x = stof(fileValue);
//		inFile >> fileValue;
//		m_indexedVertices[i].y = stof(fileValue);
//		inFile >> fileValue;
//		m_indexedVertices[i].z = stof(fileValue);
//	}
//	inFile >> m_numColors;
//	m_indexedColors = new Color[m_numColors];
//	for (int i = 0; i < m_numColors; i++)
//	{
//		inFile >> fileValue;
//		m_indexedColors[i].r = stof(fileValue);
//		inFile >> fileValue;
//		m_indexedColors[i].g = stof(fileValue);
//		inFile >> fileValue;
//		m_indexedColors[i].b = stof(fileValue);
//	}
//	inFile >> m_numIndices;
//	m_indices = new GLushort[m_numIndices];
//	for (int i = 0; i < m_numIndices; i++)
//	{
//		inFile >> fileValue;
//		m_indices[i] = stoi(fileValue);
//	}
//	inFile.close();
//	return true;
//}

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
