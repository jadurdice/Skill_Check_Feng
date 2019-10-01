#pragma once

#include"system.h"

class Effect
{
public:

	Float2 pos;
	Float2 scale;
	float lifeTime;

	virtual void Update() = 0;
	virtual void Draw() = 0;

};

class MapPiece :public Effect
{
public:
	Float2 * direction;
	Float2 bornPos;
	int roomIndex;
	void Spawn(Float2 spawnPos, Float2* playerPos, int mapIndex);
	void Update();
	void Draw();
	bool isEnable();
};


#define MAPDEFTIME	(7.0f)
#define EFFECT_MAX_CNT	(5)

void UpdateEffect();
void DrawEffect();
void UpdateMapPiece();
void DrawMapPiece();
void SetMapEffectTex(int texNo);
void SetMapEffect(Float2 spawnPos, Float2* playerPos, int mapIndex);