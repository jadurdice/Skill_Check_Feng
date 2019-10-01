/*/\/\/\/\/\/\/\/\/\/\/\/\Valar_Morghulis./\/\/\/\/\/\/\/\/\/\/\/\
 /\
 ||		Header Name:���p�w�b�_�[
 ||
 ||
/\/\
 ||
 �n
\/\/\/\/\/\/\/\/\/\/\/\/\/Valar_Dohaeris.\/\/\/\/\/\/\/\/\/\/\/\/*/



#ifndef _COMMON_H_
#define _COMMON_H_

#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include<windows.h>
#include<stdio.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"input.h"
#include"main.h"
#include"debug_font.h"

#define SCREEN_WIDTH	(1280)				//�X�N���[����
#define SCREEN_HEIGHT	(720)				//�X�N���[������
#define TEXTURE_COUNT	(3)

#define R				(200)
#define PC				(int)((R)*2*D3DX_PI)
#define RADIAN			(D3DX_PI/(PC/2))
#define DRAG			(0.7f)
#define DELTATIME		(0.02f)

#define DEGREE_TO_RADIAN(deg)	(((deg)*D3DX_PI)/180)
#define RADIAN_TO_DEGREE(rad)	((180*(rad))/D3DX_PI)

#define SAFE_RELEASE(p) { if(p){ (p)->Release(); (p)=NULL; } }


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�\���̐錾
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�C�����C���ėp�ϐ�
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

inline void DebugPrintf(const char* pFormat, ...) {
#if defined(_DEBUG)|| defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif
}

inline void DebugMB(const char* pFormat, ...) {
#if defined(_DEBUG)|| defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	MessageBox(NULL, buf, "DEBUG", MB_OK);
#endif
}


#endif // !_COMMON_H_

