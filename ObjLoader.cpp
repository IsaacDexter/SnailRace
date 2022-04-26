#include "Structures.h"
#include <vector>

bool LoadOBJ(const char* path, std::vector<Vector3>& outVertices, std::vector<Vector2>& outVs, std::vector<Vector3>& outNormals);	//The & means the function will be able to modify the vectors

/*
A word on .obj files:
	-	# is a comment, just like // in C++
	-	usemtl and mtllib describe the look of the model. which will be skipped for now
	-	v is a vertex
	-	vt is the texture coordinate of one vertex
	-	vn is the normal of one vertex
	-	f is a face, represented by a trio of indices
		-	8/11/7 describes the first vertex of the triangle using indices
			-	8 says which vertex to use, (vertex 8)
			-	11 says which texture coordinate to use (texCoord 11)
			-	7 says which normal to use (normal 7)
		-	7/12/7 describes the second vertex of the triangle
		-	6/10/7 describes the third vertex of the triangle

When in blender:
	-	apply 
*/
