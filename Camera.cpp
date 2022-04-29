#include "Camera.h"

Camera::Camera(float x, float y, float z)
{
	position = new Vector3(x, y, z);
	target = new Vector3(0.0f, 0.0f, 0.0f);
	up = new Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
	delete position;
	delete target;
	delete up;
}

Vector3 Camera::getPosition()
{
	return Vector3(position->x, position->y, position->z);
}

Vector3 Camera::getDirection()
{
	return Vector3(Math::Normalise(Vector3(position->x - target->x, position->y - target->y, position->z - target->z)));
}

Vector3 Camera::getRight()
{
	return Vector3(Math::Normalise);
}

Vector3 Camera::getUp()
{
	return Vector3();
}
