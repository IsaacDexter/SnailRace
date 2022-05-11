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

	/// <summary>finds the scalar of two 3D vectors</summary>
	/// <param name="v1">the first vector</param>
	/// <param name="v2">the second vector</param>
	/// <returns>The scalar of the two vectors.</returns>
	float Dot(Vector3 v1, Vector3 v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	/// <summary></summary>
	/// <param name="position">Also called the eye, the point in the 3d world where the camera is located</param>
	/// <param name="target">also called the center, the point the camera looks at.</param>
	/// <param name="up">The upwards direction in the 3d world for this camera, for example, if the camera is level, 0, 0, 1.</param>
	/// <returns></returns>
	Matrix4 LookAt(Vector3 position, Vector3 target, Vector3 up)
	{
		Matrix4 matrix;
		Vector3 X, Y, Z;

		//Create a new coordinate system
		Z = Vector3(position.x - target.x, position.y - target.y, position.z - target.z);
		Normalise(Z);
		Y = up;
		X = Cross(Y, Z);

		//Recompute y.
		Y = Cross(Z, X);

		//The length of the cross product is equal to the area of the parallelogram, 
		//which is < 1.0 for non perpendicular unit length vectors, so normalise x and y:
		Normalise(X);
		Normalise(Z);

		matrix.m[0][0] = X.x;
		matrix.m[1][0] = X.y;
		matrix.m[2][0] = X.z;
		matrix.m[3][0] = -Dot(X, position);
		matrix.m[0][1] = Y.x;
		matrix.m[1][1] = Y.y;
		matrix.m[2][1] = Y.z;
		matrix.m[3][1] = -Dot(Y, position);
		matrix.m[0][2] = Z.x;
		matrix.m[1][2] = Z.y;
		matrix.m[2][2] = Z.z;
		matrix.m[3][2] = -Dot(Z, position);
		matrix.m[0][3] = 0.0f;
		matrix.m[1][3] = 0.0f;
		matrix.m[2][3] = 0.0f;
		matrix.m[3][3] = 1.0f;

		return matrix;
	}


}