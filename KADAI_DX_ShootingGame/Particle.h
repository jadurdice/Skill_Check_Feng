#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include<d3dx9.h>

#define PARTICLE_MAX (8192)

enum ParticleGenre
{
	P_Trace,
	P_Muzzle,
	P_Dust,
	P_Laser,
	P_Count
};

void InitParticle();
void UninitParticle();
void UpdateParticle();
void DrawParticle();
void SetParticle(int genre, D3DXVECTOR2 pos, D3DCOLOR color, int lifeFrame, float scale, float angle);

void UpdateTrace();
void DrawTrace();

void UpdateMuzzle();
void DrawMuzzle();

void UpdateDust();
void DrawDust();

void UpdateLaser();
void DrawLaser();
#endif