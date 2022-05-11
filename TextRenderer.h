#ifndef _TEXT_RENDERER_H
#define _TEXT_RENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Structures.h"
#include "Math.h"

#include <string>
#include <map>
#include <iostream>

struct Character
{
	unsigned int TextureID;	//ID handle of the glyph texture
	iVector2 Size;	//size of glyph
	iVector2 Bearing;	//Offset from baseline to left/top of glyph
	unsigned int Advance;	//Offset to advance to next glyph
};

class TextRenderer
{
public:
	TextRenderer();
	TextRenderer(int height);

	bool InitFreetype();

	bool LoadFont(FT_Library& ft, std::string path);

	~TextRenderer();

private:
	std::map<char, Character> Characters;
};


#endif // !_TEXT_RENDERER_H