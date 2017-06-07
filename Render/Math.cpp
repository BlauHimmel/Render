#include "stdafx.h"
#include "Math.h"

_INT32 Abs(_INT32 x)
{
	return x > 0 ? x : -x;
}

_FLOAT Abs(_FLOAT x)
{
	return x > 0 ? x : -x;
}

bool Equal(_FLOAT x, _FLOAT y, _FLOAT epsilon)
{
	return abs(x - y) < epsilon ? true : false;
}

_FLOAT Interpolate(_FLOAT x, _FLOAT y, _FLOAT t)
{
	return x + (y - x) * t;
}

_FLOAT Range(_FLOAT value, _FLOAT min, _FLOAT max)
{
	if (value < min)
	{
		return min;
	}
	if (value > max)
	{
		return max;
	}
	return value;
}

Vector2i::Vector2i(const Vector4f& other) : _x((_INT32)other._x), _y((_INT32)other._y)
{

}

Vector2i::Vector2i(_INT32 x, _INT32 y) : _x(x), _y(y)
{

}

Vector2i::Vector2i(const Vector2i& other) : _x(other._x), _y(other._y)
{

}

Vector2i& Vector2i::operator = (const Vector2i& other)
{
	if (&other != this)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

_FLOAT Vector2i::Length() const
{
	_FLOAT square = (_FLOAT)(_x * _x + _y * _y);
	return sqrtf(square);
}

_INT32 Vector2i::Dot(const Vector2i& v) const
{
	return _x * v._x + _y * v._y;
}

Vector2i Vector2i::operator + (const Vector2i& v) const
{
	_INT32 x = _x + v._x;
	_INT32 y = _y + v._y;
	return Vector2i(x, y);
}

Vector2i Vector2i::operator - (const Vector2i& v) const
{
	_INT32 x = _x - v._x;
	_INT32 y = _y - v._y;
	return Vector2i(x, y);
}

Vector2i Vector2i::operator * (const Vector2i& v) const
{
	_INT32 x = _x * v._x;
	_INT32 y = _y * v._y;
	return Vector2i(x, y);
}

Vector2i Vector2i::operator * (_INT32 scale) const
{
	_INT32 x = _x * scale;
	_INT32 y = _y * scale;
	return Vector2i(x, y);
}

Vector2i Vector2i::operator - () const
{
	return Vector2i(-_x, -_y);
}

bool Vector2i::operator == (const Vector2i& other) const
{
	return (_x == other._x) && (_y == other._y);
}


Vector2f::Vector2f(const Vector4f& other) : _x(other._x), _y(other._y)
{

}

Vector2f::Vector2f(_FLOAT x, _FLOAT y) : _x(x), _y(y)
{

}

Vector2f::Vector2f(const Vector2f& other) : _x(other._x), _y(other._y)
{

}

Vector2f& Vector2f::operator = (const Vector2f& other)
{
	if (&other != this)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

_FLOAT Vector2f::Length() const
{
	_FLOAT square = _x * _x + _y * _y;
	return sqrtf(square);
}

Vector2f Vector2f::Normalize()
{
	_FLOAT length = Length();
	if (length != 0)
	{
		_FLOAT inverse = 1.0f / length;
		_x *= inverse;
		_y *= inverse;
	}
	return *this;
}

_FLOAT Vector2f::Dot(const Vector2f& v) const
{
	return _x * v._x + _y * v._y;
}

Vector2f Vector2f::operator + (const Vector2f& v) const
{
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	return Vector2f(x, y);
}

Vector2f Vector2f::operator - (const Vector2f& v) const
{
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	return Vector2f(x, y);
}

Vector2f Vector2f::operator * (const Vector2f& v) const
{
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	return Vector2f(x, y);
}

Vector2f Vector2f::operator * (_FLOAT scale) const
{
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	return Vector2f(x, y);
}

Vector2f Vector2f::operator - () const
{
	return Vector2f(-_x, -_y);
}

bool Vector2f::operator == (const Vector2f& other) const
{
	return Equal(_x, other._x) && Equal(_y, other._y);
}

Vector3f::Vector3f(const Vector4f& other) : _x(other._x), _y(other._y), _z(other._z)
{

}

Vector3f::Vector3f(_FLOAT x, _FLOAT y, _FLOAT z) : _x(x), _y(y), _z(z)
{

}

Vector3f::Vector3f(const Vector3f& other) : _x(other._x), _y(other._y), _z(other._z)
{

}

Vector3f& Vector3f::operator = (const Vector3f& other)
{
	if (&other != this)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
	}
	return *this;
}

_FLOAT Vector3f::Length() const
{
	_FLOAT square = _x * _x + _y * _y + _z * _z;
	return sqrtf(square);
}

Vector3f Vector3f::Normalize()
{
	_FLOAT length = Length();
	if (length != 0)
	{
		_FLOAT inverse = 1.0f / length;
		_x *= inverse;
		_y *= inverse;
		_z *= inverse;
	}
	return *this;
}

_FLOAT Vector3f::Dot(const Vector3f& v) const
{
	return _x * v._x + _y * v._y + _z * v._z;
}

Vector3f Vector3f::Cross(const Vector3f& v) const
{
	_FLOAT x = _y * v._z - _z * v._y;
	_FLOAT y = _z * v._x - _x * v._z;
	_FLOAT z = _x * v._y - _y * v._x;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator + (const Vector3f& v) const
{
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	_FLOAT z = _z + v._z;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator - (const Vector3f& v) const
{
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	_FLOAT z = _z - v._z;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator * (const Vector3f& v) const
{
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	_FLOAT z = _z * v._z;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator * (_FLOAT scale) const
{
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	_FLOAT z = _z * scale;
	return Vector3f(x, y, z);
}

Vector3f Vector3f::operator - () const
{
	return Vector3f(-_x, -_y, -_z);
}

bool Vector3f::operator == (const Vector3f& other) const
{
	return Equal(_x, other._x) && Equal(_y, other._y) && Equal(_z, other._z);
}

Vector4f::Vector4f(const Vector3f& other) : _x(other._x), _y(other._y), _z(other._z), _w(1.0f)
{

}

Vector4f::Vector4f(_FLOAT x, _FLOAT y, _FLOAT z, _FLOAT w) : _x(x), _y(y), _z(z), _w(w)
{

}

Vector4f::Vector4f(const Vector4f& other) : _x(other._x), _y(other._y), _z(other._z), _w(other._w)
{

}

Vector4f& Vector4f::operator = (const Vector4f& other)
{
	if (&other != this)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		_w = other._w;
	}
	return *this;
}

_FLOAT Vector4f::Length() const
{
	_FLOAT square = _x * _x + _y * _y + _z * _z;
	return sqrtf(square);
}

Vector4f Vector4f::Normalize()
{
	_FLOAT length = Length();
	if (length != 0)
	{
		_FLOAT inverse = 1.0f / length;
		_x *= inverse;
		_y *= inverse;
		_z *= inverse;
	}
	return *this;
}

_FLOAT Vector4f::Dot(const Vector4f& v) const
{
	return _x * v._x + _y * v._y + _z * v._z;
}

Vector4f Vector4f::Cross(const Vector4f& v) const
{
	_FLOAT x = _y * v._z - _z * v._y;
	_FLOAT y = _z * v._x - _x * v._z;
	_FLOAT z = _x * v._y - _y * v._x;
	return Vector4f(x, y, z, 1.0f);
}

Vector4f Vector4f::operator + (const Vector4f& v) const
{
	_FLOAT x = _x + v._x;
	_FLOAT y = _y + v._y;
	_FLOAT z = _z + v._z;
	return Vector4f(x, y, z, 1.0f);
}

Vector4f Vector4f::operator - (const Vector4f& v) const
{
	_FLOAT x = _x - v._x;
	_FLOAT y = _y - v._y;
	_FLOAT z = _z - v._z;
	return Vector4f(x, y, z, 1.0f);
}

Vector4f Vector4f::operator * (const Vector4f& v) const
{
	_FLOAT x = _x * v._x;
	_FLOAT y = _y * v._y;
	_FLOAT z = _z * v._z;
	return Vector4f(x, y, z, 1.0f);
}

Vector4f Vector4f::operator * (_FLOAT scale) const
{
	_FLOAT x = _x * scale;
	_FLOAT y = _y * scale;
	_FLOAT z = _z * scale;
	return Vector4f(x, y, z, 1.0f);
}

Vector4f Vector4f::operator * (const Matrix4f& m) const
{
	return Vector4f(
		_x * m._data[0][0] + _y * m._data[1][0] + _z * m._data[2][0] + _w * m._data[3][0],
		_x * m._data[0][1] + _y * m._data[1][1] + _z * m._data[2][1] + _w * m._data[3][1],
		_x * m._data[0][2] + _y * m._data[1][2] + _z * m._data[2][2] + _w * m._data[3][2],
		_x * m._data[0][3] + _y * m._data[1][3] + _z * m._data[2][3] + _w * m._data[3][3]
		);
}

Vector4f Vector4f::operator - () const
{
	return Vector4f(-_x, -_y, -_z, 1.0f);
}

bool Vector4f::operator == (const Vector4f& other) const
{
	return Equal(_x, other._x) && Equal(_y, other._y) && Equal(_z, other._z);
}

Vector4f Interpolate(Vector4f& v1, Vector4f& v2, _FLOAT t)
{
	return Vector4f(Interpolate(v1._x, v2._x, t), Interpolate(v1._y, v2._y, t), Interpolate(v1._z, v2._z, t), 1.0f);
}

Vector3f Interpolate(Vector3f& v1, Vector3f& v2, _FLOAT t)
{
	return Vector3f(Interpolate(v1._x, v2._x, t), Interpolate(v1._y, v2._y, t), Interpolate(v1._z, v2._z, t));
}

Matrix4f::Matrix4f(
	_FLOAT a11, _FLOAT a12, _FLOAT a13, _FLOAT a14,
	_FLOAT a21, _FLOAT a22, _FLOAT a23, _FLOAT a24,
	_FLOAT a31, _FLOAT a32, _FLOAT a33, _FLOAT a34,
	_FLOAT a41, _FLOAT a42, _FLOAT a43, _FLOAT a44
	)
{
	_data[0][0] = a11; _data[0][1] = a12; _data[0][2] = a13; _data[0][3] = a14;
	_data[1][0] = a21; _data[1][1] = a22; _data[1][2] = a23; _data[1][3] = a24;
	_data[2][0] = a31; _data[2][1] = a32; _data[2][2] = a33; _data[2][3] = a34;
	_data[3][0] = a41; _data[3][1] = a42; _data[3][2] = a43; _data[3][3] = a44;
}

Matrix4f::Matrix4f(const Matrix4f& other)
{
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			_data[i][j] = other._data[i][j];
		}
	}
}

_FLOAT& Matrix4f::operator () (_INT32 i, _INT32 j)
{
	return _data[i][j];
}

Matrix4f& Matrix4f::operator = (const Matrix4f& other)
{
	if (&other != this)
	{
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				_data[i][j] = other._data[i][j];
			}
		}
	}
	return *this;
}

Matrix4f Matrix4f::Identity()
{
	Matrix4f ans;
	ans._data[0][0] = 1.0f; ans._data[0][1] = 0.0f; ans._data[0][2] = 0.0f; ans._data[0][3] = 0.0f;
	ans._data[1][0] = 0.0f; ans._data[1][1] = 1.0f; ans._data[1][2] = 0.0f; ans._data[1][3] = 0.0f;
	ans._data[2][0] = 0.0f; ans._data[2][1] = 0.0f; ans._data[2][2] = 1.0f; ans._data[2][3] = 0.0f;
	ans._data[3][0] = 0.0f; ans._data[3][1] = 0.0f; ans._data[3][2] = 0.0f; ans._data[3][3] = 1.0f;
	return ans;
}

Matrix4f Matrix4f::Zero()
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = 0.0f;
		}
	}
	return ans;
}

void Matrix4f::SetIdentity()
{
	_data[0][0] = 1.0f; _data[0][1] = 0.0f; _data[0][2] = 0.0f; _data[0][3] = 0.0f;
	_data[1][0] = 0.0f; _data[1][1] = 1.0f; _data[1][2] = 0.0f; _data[1][3] = 0.0f;
	_data[2][0] = 0.0f; _data[2][1] = 0.0f; _data[2][2] = 1.0f; _data[2][3] = 0.0f;
	_data[3][0] = 0.0f; _data[3][1] = 0.0f; _data[3][2] = 0.0f; _data[3][3] = 1.0f;
}

void Matrix4f::SetZero()
{
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			_data[i][j] = 0.0f;
		}
	}
}

void Matrix4f::SetTranslation(_FLOAT x, _FLOAT y, _FLOAT z)
{
	SetIdentity();
	_data[3][0] = x;
	_data[3][1] = y;
	_data[3][2] = z;
}

void Matrix4f::SetScale(_FLOAT x, _FLOAT y, _FLOAT z)
{
	SetIdentity();
	_data[0][0] = x;
	_data[1][1] = y;
	_data[2][2] = z;
}

void Matrix4f::SetRotation(Vector4f& axis, _FLOAT theta)
{
	_FLOAT halfTheta = theta * 0.5f;
	_FLOAT sinHalfTheta = sinf(halfTheta);
	_FLOAT cosHalfTheta = cosf(halfTheta);
	Vector4f axisNormal = axis.Normalize();

	_FLOAT x = axisNormal._x * sinHalfTheta;
	_FLOAT y = axisNormal._y * sinHalfTheta;
	_FLOAT z = axisNormal._z * sinHalfTheta;
	_FLOAT w = cosHalfTheta;

	_FLOAT x2 = x * x; _FLOAT y2 = y * y; _FLOAT z2 = z * z;
	_FLOAT xy = x * y; _FLOAT xz = x * z; _FLOAT yz = y * z;
	_FLOAT xw = x * w; _FLOAT yw = y * w; _FLOAT zw = z * w;

	_data[0][0] = 1 - 2 * (y2 + z2);
	_data[1][0] = 2 * (xy - zw);
	_data[2][0] = 2 * (xz + yw);
	_data[3][0] = 0.0f;

	_data[0][1] = 2 * (xy + zw);
	_data[1][1] = 1 - 2 * (x2 + z2);
	_data[2][1] = 2 * (yz - xw);
	_data[3][1] = 0.0f;

	_data[0][2] = 2 * (xz - yw);
	_data[1][2] = 2 * (yz + xw);
	_data[2][2] = 1 - 2 * (x2 + y2);
	_data[3][2] = 0.0f;

	_data[0][3] = 0.0f;
	_data[1][3] = 0.0f;
	_data[2][3] = 0.0f;
	_data[3][3] = 1.0f;
}

Matrix4f Matrix4f::operator + (const Matrix4f& m) const
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = _data[i][j] + m._data[i][j];
		}
	}
	return ans;
}

Matrix4f Matrix4f::operator - (const Matrix4f& m) const
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = _data[i][j] - m._data[i][j];
		}
	}
	return ans;
}

Matrix4f Matrix4f::operator * (const Matrix4f& m) const
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = 
				_data[i][0] * m._data[0][j] + 
				_data[i][1] * m._data[1][j] +
				_data[i][2] * m._data[2][j] +
				_data[i][3] * m._data[3][j];
		}
	}
	return ans;
}

Matrix4f Matrix4f::operator * (_FLOAT scale) const
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = scale * _data[i][j];
		}
	}
	return ans;
}

Matrix4f Matrix4f::operator - () const
{
	Matrix4f ans;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			ans._data[i][j] = -_data[i][j];
		}
	}
	return ans;
}

bool Matrix4f::operator == (const Matrix4f& other) const
{
	bool equal = true;
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			if (Equal(_data[i][j], other._data[i][j]) == false)
			{
				return false;
			}
		}
	}
	return true;
}