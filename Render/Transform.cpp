#include "stdafx.h"
#include "Transform.h"

Transform::Transform(Matrix4f worldTransform, Matrix4f viewTransform, Matrix4f perspectiveTransform,
	_INT32 width, _INT32 height)
{
	_worldTransform = worldTransform;
	_viewTransform = viewTransform;
	_perspectiveTransform = perspectiveTransform;
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
	_width = width;
	_height = height;
}

Transform::Transform(const Transform& other)
{
	_worldTransform = other._worldTransform;
	_viewTransform = other._viewTransform;
	_perspectiveTransform = other._perspectiveTransform;
	_width = other._width;
	_height = other._height;
}

void Transform::Init(_INT32 width, _INT32 height)
{
	_FLOAT aspect = (_FLOAT)width / (_FLOAT)height;
	_width = width;
	_height = height;
	_worldTransform.SetIdentity();
	_viewTransform.SetIdentity();
	_perspectiveTransform.SetIdentity();
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}

void Transform::Init(Camera* camera, _INT32 width, _INT32 height, Matrix4f wordTransform)
{
	_FLOAT aspect = (_FLOAT)width / (_FLOAT)height;
	_width = width;
	_height = height;
	_worldTransform = wordTransform;
	_viewTransform = camera->GetViewTransformMatrix();
	_perspectiveTransform = camera->GetPerspectiveTransformMarix();
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}

Vector4f Transform::ApplyTransform(const Vector4f& v) const
{
	return v * _transform;
}

_INT32 Transform::CheckCVV(const Vector4f& v) const
{
	_FLOAT w = v._w;
	_INT32 check = 0;
	if (v._z < 0)
	{
		check |= 0x01;
	}
	if (v._z > w)
	{
		check |= 0x02;
	}
	if (v._x < -w)
	{
		check |= 0x04;
	}
	if (v._x > w)
	{
		check |= 0x08;
	}
	if (v._y < -w)
	{
		check |= 0x10;
	}
	if (v._y > w)
	{
		check |= 0x20;
	}
	return check;
}

Vector4f Transform::Homogenize(const Vector4f& v) const
{
	_FLOAT inverse = 1.0f / v._w;
	return Vector4f(
			(v._x * inverse + 1.0f) * _width * 0.5f,
			(1.0f - v._y * inverse) * _height * 0.5f,
			v._z * inverse,
			1.0f
		);
}

void Transform::UpdateTransform()
{
	_transform = _worldTransform * _viewTransform * _perspectiveTransform;
}