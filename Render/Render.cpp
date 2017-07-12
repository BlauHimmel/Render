
#include "stdafx.h"
#include "Math.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Device.h"
#include "Camera.h"
#include "Window.h"
#include "Image.h"
#include <iostream>

Mesh mesh = Mesh("Box", 8);

void InitMesh()
{
	mesh._vertices[0] = Vertex(Vector4f( 1, -1,  1, 1), 0, 0, Color(1.0f, 0.2f, 0.2f));
	mesh._vertices[1] = Vertex(Vector4f(-1, -1,  1, 1), 0, 1, Color(0.2f, 1.0f, 0.2f));
	mesh._vertices[2] = Vertex(Vector4f(-1,  1,  1, 1), 1, 1, Color(0.2f, 0.2f, 1.0f));
	mesh._vertices[3] = Vertex(Vector4f( 1,  1,  1, 1), 1, 0, Color(1.0f, 0.2f, 1.0f));
	mesh._vertices[4] = Vertex(Vector4f( 1, -1, -1, 1), 0, 0, Color(1.0f, 1.0f, 0.2f));
	mesh._vertices[5] = Vertex(Vector4f(-1, -1, -1, 1), 0, 1, Color(0.2f, 1.0f, 1.0f));
	mesh._vertices[6] = Vertex(Vector4f(-1,  1, -1, 1), 1, 1, Color(1.0f, 0.3f, 0.3f));
	mesh._vertices[7] = Vertex(Vector4f( 1,  1, -1, 1), 1, 0, Color(0.2f, 1.0f, 0.3f));
}


void DrawPlane(Device& device, _INT32 a, _INT32 b, _INT32 c, _INT32 d) {
	
	Vertex p1 = mesh._vertices[a]; 
	Vertex p2 = mesh._vertices[b];
	Vertex p3 = mesh._vertices[c];
	Vertex p4 = mesh._vertices[d];
	
	p1._u = 0; 
	p1._v = 0;

	p2._u = 0; 
	p2._v = 1;

	p3._u = 1;
	p3._v = 1;

	p4._u = 1; 
	p4._v = 0;
	
	device.RenderTriangle(p1, p2, p3);
	device.RenderTriangle(p3, p4, p1);
}

void DrawBox(Device& device, _FLOAT theta, _FLOAT x, _FLOAT y)
{
	Matrix4f worldTransform1;
	worldTransform1.SetRotation(Vector4f(-1.0f, -0.5f, 1.0f, 0.0f), theta);
	Matrix4f worldTransform2;
	worldTransform2.SetTranslation(x, y, 0.0f);
	device._transform->_worldTransform = worldTransform1 * worldTransform2;
	device._transform->UpdateTransform();

	DrawPlane(device, 0, 1, 2, 3);
	DrawPlane(device, 4, 5, 6, 7);
	DrawPlane(device, 0, 4, 5, 1);
	DrawPlane(device, 1, 5, 6, 2);
	DrawPlane(device, 2, 6, 7, 3);	
	DrawPlane(device, 3, 7, 4, 0);		
}

void InitTexture(Device& device)
{
	Image* tga = Image::LoadTGA("Texture2.tga");
	
	static _UINT32 texture[200][200];
	for (auto i = 0; i < tga->Height(); i++)
	{
		for (auto j = 0; j < tga->Width(); j++)
		{
			Color color = tga->GetPixel(i, j);
			_INT32 x = i / 32, y = j / 32;
			texture[i][j] = ((_INT32)(color._r * 255.0f) << 16) | 
				((_INT32)(color._g * 255.0f) << 8) | 
				((_INT32)(color._b * 255.0f) << 0);
		}
	}

	//static _UINT32 texture[256][256];
	//for (auto i = 0; i < 256; i++)
	//{
	//	for (auto j = 0; j < 256; j++)
	//	{
	//		_INT32 x = i / 32, y = j / 32;
	//		texture[i][j] = ((x + y) & 1) ? 0xffffff : 0x3fbc1f;
	//	}
	//}

	device.SetTexture(texture, tga->Width() * 4 * BYTE_SIZE, tga->Width(), tga->Height());
}

void CameraPrepare(Device& device, Vector4f& position)
{
	Vector4f target = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4f direction = target - position;
	Vector4f up = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
	_FLOAT aspect = (_FLOAT)device._transform->_width / (_FLOAT)device._transform->_height;
	Camera camera = Camera(position, direction, up, aspect, HALF_PI * 0.66f, 1.0f, 500.0f);
	device._transform->_viewTransform = camera.GetViewTransformMatrix();
	device._transform->_perspectiveTransform = camera.GetPerspectiveTransformMarix();
	device._transform->UpdateTransform();
}

int main()
{
	Device device = Device();
	Window window = Window();
	InitMesh();

	_INT32 renderState[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
	_INT32 index = 0;
	bool pressed = false;

	_FLOAT alpha = 1.0f;
	_FLOAT pos = -3.5f;

	_FLOAT up = 0.0f;
	_FLOAT left = 0.0f;
	
	SYSTEMTIME sys;
	_INT32 frame = 0;
	WORD lastTime = 0;
	GetLocalTime(&sys);
	lastTime = sys.wSecond;

	const _INT32 width = 1440;
	const _INT32 height = 900;

	LPTSTR title = _T("Mini3d  - ")
		_T("Left/Right: rotation, Up/Down: forward/backward, Space: switch render state, W/S/A/D: move");

	if (window.Init(width, height, title) != 0)
	{
		return -1;
	}

	device.Init(width, height, window._screenBuffer);
	InitTexture(device);
	device._renderState = RENDER_STATE_WIREFRAME;

	while (window._screenExit == false && window._keyDown[VK_ESCAPE] == false)
	{
		window.Dispatch();
		device.ClearBuffer(false);
		CameraPrepare(device, Vector4f(0.0f, 0.0f, pos, 1.0f));
		DrawBox(device, alpha, -left, -up);
		window.Update();
		Sleep(5);

		GetLocalTime(&sys);
		frame++;		
		WORD delta = sys.wSecond - lastTime;
		if (delta > 1)
		{
			window.SetFPS(frame / (INT32)delta);
			frame = 0;
			lastTime = sys.wSecond;
		}

		if (window._keyDown['W'] == true)
		{
			up -= 0.05f;
		}
		if (window._keyDown['S'] == true)
		{
			up += 0.05f;
		}
		if (window._keyDown['A'] == true)
		{
			left += 0.05f;
		}
		if (window._keyDown['D'] == true)
		{
			left -= 0.05f;
		}	
		if (window._keyDown[VK_UP] == true)
		{
			pos -= 0.05f;
		}
		if (window._keyDown[VK_DOWN] == true)
		{
			pos += 0.05f;
		}
		if (window._keyDown[VK_LEFT] == true)
		{
			alpha += 0.05f;
		}
		if (window._keyDown[VK_RIGHT] == true)
		{
			alpha -= 0.05f;
		}
		if (window._keyDown[VK_SPACE] == true)
		{
			if (pressed == false)
			{
				pressed = true;
				if (++index >= 3)
				{
					index = 0;
				}
				device._renderState = renderState[index];
			}
		}
		else 
		{
			pressed = false;
		}

		
	}
	return 0;
}



