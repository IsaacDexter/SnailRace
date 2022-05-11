#include "Camera.h"


Camera::Camera(float x, float y, float z)
{
	position = Vector3(x, y, z);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	front = Vector3(0.0f, 0.0f, -1.0f);

	speed = 0.125f;
}

Camera::~Camera()
{

}


void Camera::Input(char key)
{
	if (key == 'w')
	{
		position = Vector3(position.x + (speed * front.x), position.y + (speed * front.y), position.z + (speed * front.z));
	}
	if (key == 's')
	{
		position = Vector3(position.x - (speed * front.x), position.y - (speed * front.y), position.z - (speed * front.z));
	}
	if (key == 'a')
	{
		Vector3 changeVector = Math::Normalise(Math::Cross(front, up));
		position = Vector3(position.x - (speed * changeVector.x), position.y - (speed * changeVector.y), position.z - (speed * changeVector.z));
	}
	if (key == 'd')
	{
		Vector3 changeVector = Math::Normalise(Math::Cross(front, up));
		position = Vector3(position.x + (speed * changeVector.x), position.y + (speed * changeVector.y), position.z + (speed * changeVector.z));
	}
}

/// <summary>Runs gluLookAt with the updated positions from input</summary>
void Camera::Update()
{
	gluLookAt(position.x, position.y, position.z, position.x + front.x, position.y + front.y, position.z + front.z, up.x, up.y, up.z);
}

Vector3 Camera::getPosition()
{
	return Vector3(position);
}

void Camera::setPosition(Vector3 cameraPosition)
{
	position = cameraPosition;
}

Vector3 Camera::getDirection()
{
	return Vector3(Math::Normalise(Vector3(position.x - target.x, position.y - target.y, position.z - target.z)));
}

void Camera::setDirection(float pitch, float roll, float yaw)
{
	Vector3 direction;
	direction.x = cos(RADIANS(-yaw)) * cos(RADIANS(pitch));
	direction.y = sin(RADIANS(pitch));
	direction.z = sin(RADIANS(-yaw)) * cos(RADIANS(pitch));
	front = Math::Normalise(direction);
}

Vector3 Camera::getRight()
{
	return Math::Cross(up, getDirection());
}

Vector3 Camera::getUp()
{
	return Math::Cross(getDirection(), getRight());
}



float Camera::getSpeed()
{
	return speed;
}

void Camera::setSpeed(float cameraSpeed)
{
	speed = cameraSpeed;
}

Matrix4 Camera::getView()
{
	return(Math::LookAt(position, target, up));
}
