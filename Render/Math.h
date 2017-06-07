
#include <math.h>
#include "Typedef.h"

#ifndef _MATH_H
#define _MATH_H

class Vector2f;
class Vector3f;
class Vector4f;
class Matrix4f;

_INT32 Abs(_INT32 x);

_FLOAT Abs(_FLOAT x);

template<class T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

bool Equal(_FLOAT x, _FLOAT y, _FLOAT epsilon = 0.000001f);

_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t);

_FLOAT Range(_FLOAT value, _FLOAT min, _FLOAT max);

class Vector2i
{

public:

	_INT32 _x, _y;

public:

	Vector2i(){}

	Vector2i(const Vector4f& other);

	Vector2i(_INT32 x, _INT32 y);

	Vector2i(const Vector2i& other);

	Vector2i& operator = (const Vector2i& other);

public:

	_FLOAT Length() const;

	_INT32 Dot(const Vector2i& v) const;

	Vector2i operator + (const Vector2i& v) const;

	Vector2i operator - (const Vector2i& v) const;

	Vector2i operator * (const Vector2i& v) const;

	Vector2i operator * (_INT32 scale) const;

	Vector2i operator - () const;

	bool operator == (const Vector2i& other) const;

};

class Vector2f
{

public:

	_FLOAT _x, _y;

public:

	Vector2f(){}

	Vector2f(const Vector4f& other);

	Vector2f(_FLOAT x, _FLOAT y);

	Vector2f(const Vector2f& other);

	Vector2f& operator = (const Vector2f& other);

public:

	_FLOAT Length() const;

	Vector2f Normalize();

	_FLOAT Dot(const Vector2f& v) const;

	Vector2f operator + (const Vector2f& v) const;

	Vector2f operator - (const Vector2f& v) const;

	Vector2f operator * (const Vector2f& v) const;

	Vector2f operator * (_FLOAT scale) const;

	Vector2f operator - () const;

	bool operator == (const Vector2f& other) const;

};

class Vector3f
{

public:

	_FLOAT _x, _y, _z;

public:

	Vector3f(){}

	Vector3f(const Vector4f& other);

	Vector3f(_FLOAT x, _FLOAT y, _FLOAT z);

	Vector3f(const Vector3f& other);

	Vector3f& operator = (const Vector3f& other);

public:

	_FLOAT Length() const;

	Vector3f Normalize();

	_FLOAT Dot(const Vector3f& v) const;

	Vector3f Cross(const Vector3f& v) const;

	Vector3f operator + (const Vector3f& v) const;

	Vector3f operator - (const Vector3f& v) const;

	Vector3f operator * (const Vector3f& v) const;

	Vector3f operator * (_FLOAT scale) const;

	Vector3f operator - () const;

	bool operator == (const Vector3f& other) const;

};

class Vector4f
{

public:

	_FLOAT _x, _y, _z, _w;

public:
	
	Vector4f(){}

	Vector4f(const Vector3f& other);

	Vector4f(_FLOAT x, _FLOAT y, _FLOAT z, _FLOAT w);
	
	Vector4f(const Vector4f& other);
	
	Vector4f& operator = (const Vector4f& other);

public:

	_FLOAT Length() const;
	
	Vector4f Normalize();
	
	_FLOAT Dot(const Vector4f& v) const;
	
	Vector4f Cross(const Vector4f& v) const;

	Vector4f operator + (const Vector4f& v) const;
	
	Vector4f operator - (const Vector4f& v) const;
	
	Vector4f operator * (const Vector4f& v) const;
	
	Vector4f operator * (_FLOAT scale) const;

	Vector4f operator * (const Matrix4f& m) const;
	
	Vector4f operator - () const;

	bool operator == (const Vector4f& other) const;

};

Vector4f Interpolate(Vector4f& v1, Vector4f& v2, _FLOAT t);

Vector3f Interpolate(Vector3f& v1, Vector3f& v2, _FLOAT t);

class Matrix4f
{

public:

	_FLOAT _data[4][4];

public:

	Matrix4f(){};
	
	Matrix4f(
		_FLOAT a11, _FLOAT a12, _FLOAT a13, _FLOAT a14,
		_FLOAT a21, _FLOAT a22, _FLOAT a23, _FLOAT a24,
		_FLOAT a31, _FLOAT a32, _FLOAT a33, _FLOAT a34,
		_FLOAT a41, _FLOAT a42, _FLOAT a43, _FLOAT a44
		);
	
	Matrix4f(const Matrix4f& other);

	_FLOAT& operator () (_INT32 i, _INT32 j);

	Matrix4f& operator = (const Matrix4f& other);

public:

	static Matrix4f Identity();

	static Matrix4f Zero();

	void SetIdentity();

	void SetZero();

	void SetTranslation(_FLOAT x, _FLOAT y, _FLOAT z);

	void SetScale(_FLOAT x, _FLOAT y, _FLOAT z);

	void SetRotation(Vector4f& axis, _FLOAT theta);

	Matrix4f operator + (const Matrix4f& m) const;

	Matrix4f operator - (const Matrix4f& m) const;

	Matrix4f operator * (const Matrix4f& m) const;

	Matrix4f operator * (_FLOAT scale) const;

	Matrix4f operator - () const;

	bool operator == (const Matrix4f& other) const;

};

#endif
