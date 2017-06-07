#include "Transform.h"
#include "Color.h"
#include "Scanline.h"
#include "Trapezoid.h"
#include "Triangle.h"
#include <string.h>
#include <assert.h>

#ifndef _DEVICE_H
#define _DEVICE_H

class Device
{

public:

	_PVOID _buffer;
	_UINT32** _frameBuffer;
	_FLOAT** _zBuffer;
	_UINT32** _texture;

	Transform* _transform;
	_INT32 _width, _height;
	_INT32 _textWidth, _textHeight;
	_FLOAT _maxU, _maxV;
	_INT32 _renderState;
	_UINT32 _background, _foreground;

public:

	Device(){ _transform = new Transform(); }

	~Device(){ delete _transform; }

public:

	void Init(_INT32 width, _INT32 height, _PVOID buffer);

	void Destroy();

	void SetTexture(_PVOID bit, _LONG pitch, _INT32 width, _INT32 height);

	void ClearBuffer(bool background);

	void inline DrawPixel(_INT32 x, _INT32 y, _UINT32 color);

	void DrawLine(Vector2i& v1, Vector2i& v2, _UINT32 color);

	_UINT32 ReadTexture(_FLOAT u, _FLOAT v) const;

	void DrawScanline(Scanline& scanline);

	void RenderTrapezoid(Trapezoid& trapezoid);

	void RenderTriangle(Vertex& v1, Vertex& v2, Vertex& v3);

};

#endif