#include "Math.h"

#ifndef _CAMERA_H
#define _CAMERA_H

class Camera
{
	
public:

	Vector3f _position, _direction, _up, _horizontal;
	_FLOAT _aspect, _angle, _near, _far;

public:

	Camera(){}

	Camera(Vector3f position, Vector3f direction, Vector3f up,
		_FLOAT aspect, _FLOAT angle, _FLOAT near, _FLOAT far);

	Camera(Camera& other);

public:

	Matrix4f GetViewTransformMatrix();

	static Matrix4f GetViewTransformMatrix(Vector4f position, Vector4f direction, Vector4f up);

	Matrix4f GetPerspectiveTransformMarix();

	static Matrix4f GetPerspectiveTransformMarix(_FLOAT angle, _FLOAT aspect, _FLOAT near, _FLOAT far);

};

#endif