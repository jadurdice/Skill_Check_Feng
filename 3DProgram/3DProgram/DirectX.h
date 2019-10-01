#ifndef DIRECTX_H_
#define DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

// 構造体宣言
typedef struct _VERTEX
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
}VERTEX;

bool InitDirectX(HWND window_handle);
void UpdateDirextX(void);
void DrawDirectX(void);

#endif