#define _CRT_SECURE_NO_WARNINGS

#include "MeshLoader.h"
#include <vector>


using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)	//Load the vertices from the file
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh) //load the texture coords from the file.
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)	//Load the Normals for each vertex from the file
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)	//Lastly, load the indeces from the file which tell how the vertexes are spaced.
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}

	//Mesh* MeshLoader::LoadObj(char* path)
	//{
	//	/*
	//	A word on .obj files:
	//		-	# is a comment, just like // in C++
	//		-	usemtl and mtllib describe the look of the model. which will be skipped for now
	//		-	v is a vertex
	//		-	vt is the texture coordinate of one vertex
	//		-	vn is the normal of one vertex
	//		-	f is a face, represented by a trio of indices
	//			-	8/11/7 describes the first vertex of the triangle using indices
	//				-	8 says which vertex to use, (vertex 8)
	//				-	11 says which texture coordinate to use (texCoord 11)
	//				-	7 says which normal to use (normal 7)
	//			-	7/12/7 describes the second vertex of the triangle
	//			-	6/10/7 describes the third vertex of the triangle

	//	When in blender:
	//		-	apply modifers
	//		-	include normals
	//		-	include UVs
	//		-	triagulate faces
	//		-	objects as obj objects
	//	*/

	//	Mesh* mesh = new Mesh();

	//	ifstream inFile;

	//	inFile.open(path);

	//	FILE* file = fopen(path, "r");
	//	if (file == NULL) {
	//		cerr << "Can't open model file" << endl;
	//		return nullptr;
	//	}

	//	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	//	std::vector< Vector3 > tempVertices;
	//	std::vector< Vector2 > tempUvs;
	//	std::vector< Vector3 > tempNormals;

	//	while (true)
	//	{
	//		char lineHeader[128];	//Read the first word of the line
	//		int res = fscanf(file, "%s", lineHeader);	//Formats the file input to look for a word that is a string, i.e. v, vt, vn, or f.
	//		if (res == EOF)
	//		{
	//			break;	//If hit the End of File, exit by breaking the loop
	//		}
	//		else	//parse lineHeader
	//		{
	//			if (strcmp(lineHeader, "v") == 0)	//If the file header is v, strcmp (string compare) will return 0. 
	//			{	//v, so this is a vertex, containing 3 floats
	//				Vector3 vertex;
	//				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);	//Format the file input to look for 3 floats, in format v 1.000000 1.000000 -1.000000
	//				tempVertices.push_back(vertex);	//Push the vertex onto the vector containing the vertices
	//			}
	//			else if (strcmp(lineHeader, "vt") == 0)	//If the file header is vt, strcmp (string compare) will return 0. 
	//			{	//vt, so this is a uv, containing 2 floats
	//				Vector2 uv;
	//				fscanf(file, "%f %f %f\n", &uv.x, &uv.y);	//Format the file input to look for 2 floats, in format vt 0.875000 0.500000
	//				tempUvs.push_back(uv);	//Push the uv onto the vector containing the uvs
	//			}
	//			else if (strcmp(lineHeader, "vn") == 0)	//If the file header is vn, strcmp (string compare) will return 0. 
	//			{	//vn, so this is a normal, containing 3 floats
	//				Vector3 normal;
	//				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);	//Format the file input to look for 3 floats, in format vn 0.0000 1.0000 0.0000
	//				tempNormals.push_back(normal);	//Push the normal onto the vector containing the normals
	//			}
	//			else if (strcmp(lineHeader, "f") == 0)	//If the file header is f, strcmp (string compare) will return 0. 
	//			{	//f, so this is a face, containing 3 sets of vertices, uvs and normals
	//				std::string vertex1, vertex2, vertex3;
	//				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	//				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);//Format the file input to look for 3 floats, in format vn 0.0000 1.0000 0.0000
	//				if (matches != 9)
	//				{
	//					cerr << "File could not be read by parser. Only " << matches << "/9 matches made. See readme for instructions on exporting .obj s." << endl;
	//					return nullptr;
	//				}
	//				vertexIndices.push_back(vertexIndex[0]);	//push the first vertex index onto the vertex indices vector
	//				vertexIndices.push_back(vertexIndex[1]);	//push the second vertex index onto the vertex indices vector
	//				vertexIndices.push_back(vertexIndex[2]);	//push the third vertex index onto the vertex indices vector
	//				uvIndices.push_back(uvIndex[0]);	//push the first uv index onto the uv indices vector
	//				uvIndices.push_back(uvIndex[1]);	//push the second uv index onto the uv indices vector
	//				uvIndices.push_back(uvIndex[2]);	//push the third uv index onto the uv indices vector
	//				normalIndices.push_back(normalIndex[0]);	//push the first normal index onto the normal indices vector
	//				normalIndices.push_back(normalIndex[1]);	//push the second normal index onto the normal indices vector
	//				normalIndices.push_back(normalIndex[2]);	//push the third normal index onto the normal indices vector
	//			}
	//		}
	//	}
	//	mesh->VertexCount = vertexIndices.size();
	//	mesh->Vertices = new Vertex[mesh->VertexCount];
	//	for (unsigned int i = 0; i < mesh->VertexCount; i++)	//for each vertex of each triangle
	//	{
	//		unsigned int vertexIndex = vertexIndices[i];
	//		Vector3 vertex = tempVertices[vertexIndex - 1];	//the position of the vertex (c++ indexing starts at 0 unlike obj's 1, hence the -1
	//		
	//		mesh->Vertices[i].x = vertex.x;
	//		mesh->Vertices[i].y = vertex.y;
	//		mesh->Vertices[i].z = vertex.z;
	//	}
	//	mesh->TexCoordCount = uvIndices.size();
	//	mesh->TexCoords = new TexCoord[mesh->TexCoordCount];
	//	for (unsigned int i = 0; i < mesh->TexCoordCount; i++)	//for each uv of each triangle
	//	{
	//		unsigned int uvIndex = uvIndices[i];
	//		Vector2 vertex = tempUvs[uvIndex - 1];	//the position of the uv (c++ indexing starts at 0 unlike obj's 1, hence the -1

	//		mesh->TexCoords[i].u = vertex.x;
	//		mesh->TexCoords[i].v = vertex.y;
	//	}
	//	mesh->NormalCount = normalIndices.size();
	//	mesh->Normals = new Vector3[mesh->NormalCount];
	//	for (unsigned int i = 0; i < mesh->NormalCount; i++)	//for each normal of each triangle
	//	{
	//		unsigned int normalIndex = normalIndices[i];
	//		Vector3 vertex = tempNormals[normalIndex - 1];	//the position of the normal (c++ indexing starts at 0 unlike obj's 1, hence the -1

	//		mesh->Normals[i].x = vertex.x;
	//		mesh->Normals[i].y = vertex.y;
	//		mesh->Normals[i].z = vertex.z;
	//	}
	//	mesh->IndexCount = vertexIndices.size();
	//	mesh->Indices = new Index[mesh->IndexCount];
	//	for (unsigned int i = 0; i < mesh->IndexCount; i++)	//for each index of each triangle
	//	{
	//		mesh->Indices[i].vertex = vertexIndices[i];
	//		mesh->Indices[i].uv = uvIndices[i];
	//		mesh->Indices[i].normal = normalIndices[i];
	//	}
	//	return mesh;
	//}
}