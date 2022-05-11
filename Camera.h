#ifndef _CAMERA_H
#define _CAMERA_H

#include "Structures.h"
#include "Math.h"

class Camera
{
private:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 front;
	float speed;
public:
	Camera(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Camera();

	void Input(char key);
	void Update();

	Vector3 getPosition();
	void setPosition(Vector3 cameraPosition);
	Vector3 getDirection();
	void setDirection(float pitch, float roll, float yaw);
	Vector3 getRight();
	Vector3 getUp();
	Vector3 getViewport();
	float getSpeed();
	void setSpeed(float cameraSpeed);
	Matrix4 getView();
};

#endif // !_CAMERA_H



