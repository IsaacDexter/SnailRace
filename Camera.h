#ifndef _CAMERA_H
#define _CAMERA_H

#include "Structures.h"
#include "Math.h"

class Camera
{
private:
	Vector3* position;
	Vector3* target;
	Vector3* up;
public:
	Camera(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Camera();

	Vector3 getPosition();
	Vector3 getDirection();
	Vector3 getRight();
	Vector3 getUp();
};

#endif // !_CAMERA_H



