
#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#define PI						3.1415926f
#define HALF_PI					1.5707963f

#define COLOR_MIN				0.0f
#define COLOR_MAX				1.0f

#define RENDER_STATE_WIREFRAME	0x01
#define RENDER_STATE_TEXTURE	0x02
#define RENDER_STATE_COLOR		0x04

#define TEXTURE_MAX_SIZE	    1024

#define PTR_SIZE				sizeof(_PVOID)
#define BYTE_SIZE				sizeof(_BYTE)

using _DOUBLE	=				double;
using _FLOAT	=				float;
using _LONG		=				long;
using _INT32	=				int;
using _UINT32	=				unsigned int;
using _CHAR		=				char;
using _BYTE		=				char;
using _PSTR		=				char*;
using _PBYTE	=				char*;
using _PVOID	=				void*;

#endif