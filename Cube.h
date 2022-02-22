#ifndef _CUBE_H
#define _CUBE_H

#include "Primitive.h"

class Cube :
    public Primitive
{
private:
    GLushort numberOfTriangles = 36;
};

#endif // !_CUBE_H