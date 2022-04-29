#include "Math.h"

namespace Math
{
	/// <summary>Normalise the vector setting its length to 1</summary>
	/// <param name="v">the vector to normalise</param>
	/// <returns>the normalised vector</returns>
	Vector3 Normalise(Vector3 vector)
	{
		float vectorLength = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
		return Vector3(vector.x / vectorLength, vector.y / vectorLength, vector.z / vectorLength);
	}
	/// <summary>Finds the cross project of vector v1 and vector v2</summary>
	/// <param name="v1">the first vector</param>
	/// <param name="v2">the second vector. Remember order matters.</param>
	/// <returns>the cross product.</returns>
	Vector3 Cross(Vector3 v1, Vector3 v2)
	{
		return Vector3((v1.y * v2.z) - (v2.y * v1.z), (v1.z * v2.x) - (v2.z * v1.x), (v1.x * v2.y) - (v2.x - v1.y));
	}
}