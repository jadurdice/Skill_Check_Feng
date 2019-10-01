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

//�X�v���C�g��`���֐�
//int		textureID		�e�N�X�`���ԍ�
//float		dx		�n�_�w���W�i�����ł͍��オ�Z���^�[�j
//float		dy		�n�_�x���W
//int		cx		�؂���w���W
//int		cy		�؂���x���W
//int		cw		�؂���͈͂w���W
//int		ch		�؂���͈͂x���W
//float		angle	�񂷊p�x(degree)
//float		cenx	��]�̒��S���W�w	(��ʍ��W����]���̏ꍇ)	
//float		ceny	��]�̒��S���W�x	
//float		axisx	��]�̒��S���W�w	(�|���S�����W����]���̏ꍇ)	
//float		axisy	��]�̒��S���W�x	
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