#ifndef _MATH_H
#define _MATH_H

#include "Structures.h"

namespace Math
{
	Vector3 Normalise(Vector3 v1);

	Vector3 Cross(Vector3 v1, Vector3 v2);

	float Dot(Vector3 v1, Vector3 v2);

	Matrix4 LookAt(Vector3 position, Vector3 target, Vector3 up);
};

#endif // !_MATH_H