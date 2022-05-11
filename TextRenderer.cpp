#include "TextRenderer.h"

TextRenderer::TextRenderer()
{

}
/// <summary>This function creates a new instance of freetype 2 library and sets the g_freetype handle to it
/// It loads each module that freetype knows about in the library.
/// </summary>
bool TextRenderer::InitFreetype()
{
	FT_Library library;
	if (FT_Init_FreeType(&library))
	{
		std::cerr << "An error occurred during library initialisation." << std::endl;
		return false;
	}
	//Load the font.
	FT_Face face;
	if (FT_New_Face(library, "Fonts/Courier_Prime/CourierPrime-Regular.ttf", 0, &face))	//Create a new face, describing a given typeface and style.
	{
		std::cerr << "The font file  could not be loaded." << std::endl;
		return false;
	}
	//Set the size of the font to be 16 pt. 0 means same as horizontal resolution.
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	//For each of the 128 characters in the ASCII set, generate a texture 
	//and store it's relevant data into a Character struct that can be added to the characters map.
	//All data required to render each character is stored for later use.
	for (unsigned char c = 0; c < 128; c++)
	{
		//Load the character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		//Generate the texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			iVector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			iVector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));

		//Free freetypes resouces once glyphs have been processed
		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}
}

TextRenderer::TextRenderer(int height)
{
}

bool TextRenderer::LoadFont(FT_Library& ft, std::string path)
{
	return false;
}

TextRenderer::~TextRenderer()
{
}
