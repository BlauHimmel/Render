#include "Math.h"
#include "Camera.h"

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

class Transform
{

public:

	Matrix4f _worldTransform, _viewTransform, _perspectiveTransform, _transform;
	_INT32 _width, _height;

public:

	Transform(){}

	Transform(Matrix4f worldTransform, Matrix4f viewTransform, Matrix4f perspectiveTransform,
		_INT32 width, _INT32 height);

	Transform(const Transform& other);

public:

	void Init(_INT32 width, _INT32 height);

	void Init(Camera* camera, _INT32 width, _INT32 height, Matrix4f worldTransform);

	Vector4f ApplyTransform(const Vector4f& v) const;

	_INT32 CheckCVV(const Vector4f& v) const;

	Vector4f Homogenize(const Vector4f& v) const;

	void UpdateTransform();

};

#endif