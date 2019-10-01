#ifndef _SPRITE_H_
#define _SPRITE_H_

#include"common.h"
#include"texture.h"



typedef struct Vertex2d_tag {
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texChord;
}Vertex2d;

#define HOSEI (-0.5f)
#define FVF_VERTEX2D (D3DFVF_XYZRHW| D3DFVF_DIFFUSE | D3DFVF_TEX1)

//スプライトを描く関数
//int		textureID		テクスチャ番号
//float		dx		始点Ｘ座標（ここでは左上がセンター）
//float		dy		始点Ｙ座標
//int		cx		切り取りＸ座標
//int		cy		切り取りＹ座標
//int		cw		切り取り範囲Ｘ座標
//int		ch		切り取り範囲Ｙ座標
//float		angle	回す角度(degree)
//float		cenx	回転の中心座標Ｘ	(画面座標が回転軸の場合)	
//float		ceny	回転の中心座標Ｙ	
//float		axisx	回転の中心座標Ｘ	(ポリゴン座標が回転軸の場合)	
//float		axisy	回転の中心座標Ｙ	
void InitSprite(); void UninitSprite();
void DrawSpriteIndex(int textureID, float dx, float dy);
void DrawSpriteCut(int textureID, float dx, float dy, int cx, int cy, int cw, int ch);
void DrawSpriteCut(int textureID, float dx, float dy, int cx, int cy, int cw, int ch);
void DrawSpriteRotScr(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float cenx, float ceny, float scalex, float scaley);
void DrawSpriteRotPlg(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float axisx, float axisy, float scalex, float scaley);
void DrawSpriteRotCenter(int textureID, float dx, float dy, int cx, int cy, int cw, int ch, float angle, float axisx, float axisy, float scalex, float scaley);
void SetColor(int r, int g, int b, int a);
void SetColor(D3DCOLOR color);
void StartParticle();
void EndParticle();

#endif