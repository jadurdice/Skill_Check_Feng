#ifndef _FADE_H_
#define _FADE_H_
#include"common.h"
#include"sound.h"


#define FADE_NONE	(1<<0)
#define FADE_IN		(1<<1)
#define FADE_OUT	(1<<2)
#define FADE_BLACK	(1<<3)


#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

typedef struct FadeVertex_tag {
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}FadeVertex;

void InitFade();
void UnInitFade();
void UpdateFade();
void DrawFade();
void SetFade(int frame, D3DCOLOR color, bool isFadeOut);
bool GetFadeState();
void SetTrailEnable();
#endif