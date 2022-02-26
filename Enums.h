#ifndef _ENUMS_H
#define _ENUMS_H

/// <summary>Simple enum used to store currently pressed mouse buttons</summary>
enum MouseButtons
{
	none,
	LeftMouseButton,
	RightMouseButton,
	MiddleMouseButton,
};

/// <summary>Simple enum used to toggle the currently rendered shape</summary>
enum Shapes
{
	cube,
	hexagonalPrism,
	squareBasedPyramid,
	all
};

#endif // !_ENUMS_H