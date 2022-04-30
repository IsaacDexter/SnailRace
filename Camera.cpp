#include "Camera.h"

Camera::Camera(float x, float y, float z)
{
	position = Vector3(x, y, z);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{

}

/// <summary></summary>
/// <param name="rotation">I don't have the foggiest clue how to convert from userval to degrees. 158 ~= 90 degrees. Use that as you will.</param>
/// <param name="radius">The radius to orbit at.</param>
void Camera::Update(float rotation, float radius)
{
	float camX = sin(rotation) * radius;
	float camZ = cos(rotation) * radius;
	Matrix4 view;
	gluLookAt(camX, 0.0f, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//view = Math::LookAt(Vector3(camX, 0.0f, camZ), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
}

Vector3 Camera::getPosition()
{
	return Vector3(position);
}

Vector3 Camera::getDirection()
{
	return Vector3(Math::Normalise(Vector3(position.x - target.x, position.y - target.y, position.z - target.z)));
}

Vector3 Camera::getRight()
{
	return Math::Cross(up, getDirection());
}

Vector3 Camera::getUp()
{
	return Math::Cross(getDirection(), getRight());
}

Matrix4 Camera::getView()
{
	return(Math::LookAt(position, target, up));
}
