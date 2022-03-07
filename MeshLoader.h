#ifndef _MESH_LOADER_H
#define _MESH_LOADER_H

#include "Structures.h"
#include <iostream>
#include <fstream>

namespace MeshLoader
{
	Mesh* Load(char* path);
};

#endif // !_MESH_LOADER_H