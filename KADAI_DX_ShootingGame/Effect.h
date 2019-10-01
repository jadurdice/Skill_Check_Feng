#ifndef _EFFECT_H_
#define _EFFECT_H_

#include<d3dx9.h>

#define EXP_MAX (16)
#define DUST_MAX (128)

#define DUSTTEXW (98.0f)
#define DUSTTEXH (107.0f)
#define DUSTTEXU (228)
#define DUSTTEXV (0)

//height="107" width="98" y="0" x="228" name="smokeOrange5.png"/>


void InitEffect();
void UninitEffect();
void UpdateEffect();
void DrawEffect();
void SetEffect(D3DXVECTOR2 effGenePos);


#endif