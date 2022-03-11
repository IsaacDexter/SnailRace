#include "MeshLoader.h"

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

	void LoadColours(ifstream& inFile, Mesh& mesh)	//Load the colours for each vertex from the file
	{
		inFile >> mesh.ColorCount;

		if (mesh.ColorCount > 0)
		{
			mesh.Colors = new Color[mesh.ColorCount];

			for (int i = 0; i < mesh.ColorCount; i++)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
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

	void LoadIndices(ifstream& inFile, Mesh& mesh)	//Lastly, load the indeces from the file which tell how the vertexes are spaced.
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort [mesh.IndexCount];

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
		LoadColours(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}
}