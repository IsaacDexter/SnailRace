#include "Texture2D.h"

#include <fstream>
#include <iostream>
using namespace std;

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_ID);	//Same values as in the glGenTextures in load function.
}

/// <summary>Loads an image file into the ID</summary>
/// <param name="path">The path towards the texture.</param>
/// <param name="width">width in pixels of the texture.</param>
/// <param name="height">height in pixels of the texure.</param>
/// <returns>True for a successful load, false for an error.</returns>
bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;
	m_width = width;
	m_height = height;
	inFile.open(path, ios::binary);

	//if the file fails to open, report it as an error using cerr
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);	//Seek to end of the file.
	fileSize = (int)inFile.tellg();	//Get the current position in the file - this gives the total file size.
	tempTextureData = new char[fileSize];	//Create a new array of the size of the file to temporarily store data.
	inFile.seekg(0, ios::beg);	//Seek back to the beginning of the file, prepping to populate array.
	inFile.read(tempTextureData, fileSize);	//Read in all the data in one go
	inFile.close();	//Close the file, now that all data has been read from it.

	cout << path << " loaded." << endl; //Temporary debugging print statement.

	glGenTextures(1, &m_ID);	//Get next texture ID
	glBindTexture(GL_TEXTURE_2D, m_ID);	//Bind the texture to that ID
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);	//Specify details of the texture image.

	delete[] tempTextureData;	//Clear the data from memory as we don't need it anymore.
	return true;	//Load was successful!
}

GLuint Texture2D::GetID() const
{
	return m_ID;
}

int Texture2D::GetWidth() const
{
	return m_width;
}

int Texture2D::GetHeight() const
{
	return m_height;
}//
