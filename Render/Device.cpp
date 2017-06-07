#include "stdafx.h"
#include "Device.h"

/*

frameBuffer ->  |----8----|----8----|----8----|----8----|
							   R         G         B

zBuffer     ->    1 / z

|---- h * sizeof(void*)----|----height * sizeof(void*)----|----1024 * sizeof(void*)----|----w * h * 4----|----w * h * 4----|----64----|
_frameBuffer			   _zBuffer						  _texture                     frameBuffer       zBuffer		   ptr
	->frameBuffer				->zBuffer					  ->ptr		
*/

void Device::Init(_INT32 width, _INT32 height, _PVOID buffer)
{
	_INT32 need = PTR_SIZE * (height * 2 + TEXTURE_MAX_SIZE) + BYTE_SIZE * width * height * 8;
	_PBYTE ptr = new _BYTE[need + 64 * BYTE_SIZE];

	_PBYTE frameBuffer;
	_PBYTE zBuffer;

	assert(buffer != NULL);

	_buffer = ptr;
	_frameBuffer = (_UINT32**)ptr;
	ptr += PTR_SIZE * height;
	_zBuffer = (_FLOAT**)ptr;
	ptr += PTR_SIZE * height;
	_texture = (_UINT32**)ptr;
	ptr += PTR_SIZE * TEXTURE_MAX_SIZE;
	
	frameBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;
	zBuffer = ptr;
	ptr += BYTE_SIZE * width * height * 4;
	if (buffer != NULL)
	{
		frameBuffer = (_PBYTE)buffer;
	}
	for (auto i = 0; i < height; i++) 
	{
		_frameBuffer[i] = (_UINT32*)(frameBuffer + BYTE_SIZE * width * 4 * i);
		_zBuffer[i] = (_FLOAT*)(zBuffer + BYTE_SIZE * width * 4 * i);
	}
	_texture[0] = (_UINT32*)ptr;
	memset(_texture[0], 0, 64);
	_textWidth = 2;
	_textHeight = 2;
	_maxU = 1.0f;
	_maxV = 1.0f;
	_width = width;
	_height = height;
	_background = 0xc0c0c0;
	_foreground = 0;
	_transform->Init(_width, _height);
	_renderState = RENDER_STATE_WIREFRAME;
}

void Device::Destroy()
{
	if (_buffer != NULL)
	{
		delete[] _buffer;
	}
	_frameBuffer = NULL;
	_zBuffer = NULL;
	_texture = NULL;
}

void Device::SetTexture(_PVOID bit, _LONG pitch, _INT32 textWidth, _INT32 textHeight)
{
	_PBYTE ptr = (_PBYTE)bit;
	for (auto i = 0; i < textHeight; i++, ptr += pitch)
	{
		_texture[i] = (_UINT32*)ptr;
	}
	_textWidth = textWidth;
	_textHeight = textHeight;
	_maxU = (_FLOAT)(textWidth - 1);
	_maxV = (_FLOAT)(textHeight - 1);
}

void Device::ClearBuffer(bool background)
{
	for (auto i = 0; i < _height; i++)
	{
		_UINT32* dst = _frameBuffer[i];
		_UINT32 cc = (_height - 1 - i) * 230 / (_height - 1);
		cc = (cc << 16) | (cc << 8) | cc;
		if (background)
		{
			cc = _background;
		}
		for (auto j = 0; j < _width; j++)
		{
			dst[j] = cc;
		}
	}
	for (auto i = 0; i < _height; i++)
	{
		_FLOAT* dst = _zBuffer[i];
		for (auto j = 0; j < _width; j++)
		{
			dst[j] = 0.0f;
		}
	}
}

void inline Device::DrawPixel(_INT32 x, _INT32 y, _UINT32 color)
{
	if (x >= 0 && x < _width && y < _height && y >= 0) 
	{
		_frameBuffer[y][x] = color;
	}
}

void Device::DrawLine(Vector2i& v1, Vector2i& v2, _UINT32 color)
{
	if (v1 == v2)
	{
		DrawPixel(v1._x, v1._y, color);
	}
	else if (v1._x == v2._x)
	{
		_INT32 dir = v2._y > v1._y ? 1 : -1;
		for (auto y = v1._y; y != v2._y; y += dir)
		{
			DrawPixel(v1._x, y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	else if (v1._y == v2._y)
	{
		_INT32 dir = v2._x > v1._x ? 1 : -1;
		for (auto x = v1._x; x != v2._x; x += dir)
		{
			DrawPixel(x, v1._y, color);
		}
		DrawPixel(v2._x, v2._y, color);
	}
	else
	{
		_INT32 dx = Abs(v1._x - v2._x);
		_INT32 dy = Abs(v1._y - v2._y);
		_INT32 error = 0;
		if (dx > dy)
		{
			if (v1._x > v2._x)
			{
				Swap(v1._x, v2._x);
				Swap(v1._y, v2._y);
			}
			_INT32 dir = v2._y > v1._y ? 1 : -1;
			for (auto x = v1._x, y = v1._y; x <= v2._x; x++)
			{
				DrawPixel(x, y, color);
				error += dy;
				if (error >= dx)
				{
					error -= dx;
					y += dir;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(v2._x, v2._y, color);
		}
		else
		{
			if (v1._y > v2._y)
			{
				Swap(v1._x, v2._x);
				Swap(v1._y, v2._y);
			}
			_INT32 dir = v2._x > v1._x ? 1 : -1;
			for (auto y = v1._y, x = v1._x; y <= v2._y; y++)
			{
				DrawPixel(x, y, color);
				error += dx;
				if (error >= dy)
				{
					error -= dy;
					x += dir;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(v2._x, v2._y, color);
		}
	}
}

_UINT32 Device::ReadTexture(_FLOAT u, _FLOAT v) const
{
	u = u * _maxU;
	v = v * _maxV;
	_INT32 x = (_INT32)(u + 0.5f);
	_INT32 y = (_INT32)(v + 0.5f);
	x = (_INT32)Range((_FLOAT)x, 0, _maxU);
	y = (_INT32)Range((_FLOAT)y, 0, _maxV);
	return _texture[y][x];
}

void Device::DrawScanline(Scanline& scanline)
{
	_UINT32* frameBuffer = _frameBuffer[scanline._y];
	_FLOAT* zBuffer = _zBuffer[scanline._y];

	for (auto i = 0, x = scanline._x; i < scanline._width && x < _width; i++, x++)
	{
		if (x >= 0 && x < _width)
		{
			_FLOAT deepz = scanline._start._deepz;
			if (deepz >= zBuffer[x])
			{
				_FLOAT w = 1.0f / deepz;
				zBuffer[x] = deepz;
				if (_renderState & RENDER_STATE_COLOR)
				{
					Color color = scanline._start._color * w;
					_INT32 R = (_INT32)(color._r * 255.0f);
					_INT32 G = (_INT32)(color._g * 255.0f);
					_INT32 B = (_INT32)(color._b * 255.0f);
					R = (_INT32)Range((_FLOAT)R, 0.0f, 255.0f);
					G = (_INT32)Range((_FLOAT)G, 0.0f, 255.0f);
					B = (_INT32)Range((_FLOAT)B, 0.0f, 255.0f);
					frameBuffer[x] = (R << 16) | (G << 8) | (B << 0);
				}
				if (_renderState & RENDER_STATE_TEXTURE)
				{
					_FLOAT u = scanline._start._u * w; 
					_FLOAT v = scanline._start._v * w;
					frameBuffer[x] = ReadTexture(u, v);
				}
			}
		}
		scanline._start = scanline._start + scanline._step;	
	}
}

void Device::RenderTrapezoid(Trapezoid& trapezoid)
{
	_INT32 top = (_INT32)(trapezoid._top + 0.5f);
	_INT32 bottom = (_INT32)(trapezoid._bottom + 0.5f);
	for (auto i = top; i < bottom && i < _height; i++)
	{
		if (i >= 0 && i < _height)
		{
			trapezoid.GetEndPoint(i + 0.5f);
			Scanline scanline = trapezoid.InitScanline(i);
			DrawScanline(scanline);
		}
	}
}

void Device::RenderTriangle(Vertex& v1, Vertex& v2, Vertex& v3)
{
	Vector4f c1 = _transform->ApplyTransform(v1._position);
	Vector4f c2 = _transform->ApplyTransform(v2._position);
	Vector4f c3 = _transform->ApplyTransform(v3._position);

	if (_transform->CheckCVV(c1) != 0 ||
		_transform->CheckCVV(c2) != 0 ||
		_transform->CheckCVV(c3) != 0)
	{
		return;
	}

	Vector4f h1 = _transform->Homogenize(c1);
	Vector4f h2 = _transform->Homogenize(c2);
	Vector4f h3 = _transform->Homogenize(c3);

	if (_renderState & (RENDER_STATE_COLOR | RENDER_STATE_TEXTURE))
	{
		Trapezoid trapezoids[2];

		Triangle triangles = Triangle(v1, v2, v3);
		triangles._vertex1._position = h1;
		triangles._vertex2._position = h2;
		triangles._vertex3._position = h3;
		triangles._vertex1._position._w = c1._w;
		triangles._vertex2._position._w = c2._w;
		triangles._vertex3._position._w = c3._w;
		triangles._vertex1.Init();
		triangles._vertex2.Init();
		triangles._vertex3.Init();
		triangles.Sort();

		_INT32 n = Trapezoid::GetTrapezoids(triangles, trapezoids);

		if (n >= 1)
		{
			RenderTrapezoid(trapezoids[0]);
		}
		if (n >= 2)
		{
			RenderTrapezoid(trapezoids[1]);
		}
	}

	if (_renderState & RENDER_STATE_WIREFRAME)
	{
		DrawLine(Vector2i(h1), Vector2i(h2), _foreground);
		DrawLine(Vector2i(h1), Vector2i(h3), _foreground);
		DrawLine(Vector2i(h2), Vector2i(h3), _foreground);
	}
}