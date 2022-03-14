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

bool Texture2D::LoadBMP(char* path)
{
	//A UINT8 is essentially an unsigned short.
	UINT8* datBuff[2] = { nullptr, nullptr };	//header buffers.
	UINT8* pixels = nullptr;	//Pixels
	BITMAPFILEHEADER* bmpHeader = nullptr;	//Header
	BITMAPINFOHEADER* bmpInfo = nullptr;	//Info

	ifstream inFile;	//construct a buffer to hold the file.
	inFile.open(path, ios::binary);	//open up the file
	
	if (!inFile.good())	//Check if file opened correctly
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}
	
	//Allocate memory for the headers, get the values with the data buffers.
	//allocate byte memory that iwll hold the the two headers
	datBuff[0] = new UINT8[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new UINT8[sizeof(BITMAPINFOHEADER)];
	//Load the data into buffers.
	inFile.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	inFile.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

	//once the data is loaded, construct the loaded data into the headers.
	bmpHeader	= (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo		= (BITMAPINFOHEADER*)datBuff[1];

	//Now that is laoded, check if the file is a bmp file.
	if (bmpHeader->bfType != 0x4D42)
	{
		cerr << "Texture file " << path << " was not a .bmp file." << endl;
		return false;
	}

	//Allocate pixel memory.
	pixels = new UINT8[bmpInfo->biSizeImage];

	//seek to where image data starts
	inFile.seekg(bmpHeader->bfOffBits);
	//Read in image data
	inFile.read((char*)pixels, bmpInfo->biSizeImage);

	//.bmp files store image data in BGR as opposed to RGB format, so convert it to RGB
	UINT8 tempRGB = 0;	//swap buffer
	for (unsigned long i = 0; i < bmpInfo->biSizeImage; i += 3)
	{
		tempRGB = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tempRGB;
	}

	//Set width and height to the values loaded from the file.
	m_width = bmpInfo->biWidth;
	m_height = bmpInfo->biHeight;

	inFile.close();	//close the file

	cout << path << " loaded." << endl;	//Temporary debugging print statement.

	glGenTextures(1, &m_ID);	//Generate new ID
	glBindTexture(GL_TEXTURE_2D, m_ID);	//Bind that texture temporarily

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//create the texture by getting the offests from the image, then use with the image's.
	//pixel data to create it.
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	//delete temprary data
	delete[] datBuff[0];
	delete[] datBuff[1];
	delete[] pixels;

	return true;	//Texture loaded successfully!
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
