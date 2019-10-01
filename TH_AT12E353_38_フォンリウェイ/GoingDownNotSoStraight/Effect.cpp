#include"Effect.h"
#include"Game.h"
#include"sound.h"
#include"sprite.h"
#include"PauseMenu.h"


unsigned int mapTex = 0;


void MapPiece::Spawn(Float2 spawnPos, Float2* playerPos, int index)
{
	lifeTime = MAPDEFTIME;
	pos = spawnPos;
	bornPos = spawnPos;
	direction = playerPos;
	roomIndex = index;


}

void MapPiece::Update()
{
	if (lifeTime <= 0.0f) {
		return;
	}
	lifeTime -= DELTATIME*0.1f;
	if (lifeTime > MAPDEFTIME *0.8f) {
		pos = GameSystem::LerpFloat2(pos, MakeFloat2(bornPos.x,bornPos.y-64.0f), DELTATIME*0.5f);
		scale = GameSystem::LerpFloat2(scale, MakeFloat2(64.0f, 64.0f), DELTATIME);
	}
	else {
		pos = GameSystem::LerpFloat2(pos, *direction, DELTATIME*0.5f);
		scale = GameSystem::LerpFloat2(scale, MakeFloat2(0.0f, 0.0f), DELTATIME*0.5f);
		if (scale.x <= 0.1f &&scale.x >= 0.05f) {
			PlaySE(S_GETMAP);
		}
	}
}

void MapPiece::Draw()
{
	if (lifeTime <= 0.0f) {
		return;
	}

	Float2 uv;

	RoomUVSelect(uv.x, uv.y, roomIndex);

	DrawSpriteCircle(
		mapTex,
		pos.x + 0.5f*scale.x,pos.y,
		uv.x,uv.y,
		0.125f,0.125f,
		scale.x,scale.y
	);

	//‚±‚±‚Ü‚Å
}

bool MapPiece::isEnable() {
	return ( lifeTime > 0.0f );
}

MapPiece mp[5];


void UpdateEffect() {
	UpdateMapPiece();
}
void DrawEffect() {
	DrawMapPiece();
}

void UpdateMapPiece() {
	for (int i = 0; i < EFFECT_MAX_CNT; i++)
	{
		if (!mp[i].isEnable()) {
			continue;
		}
		mp[i].Update();
	}

}
void DrawMapPiece() {
	for (int i = 0; i < EFFECT_MAX_CNT; i++)
	{
		if (!mp[i].isEnable()) {
			continue;
		}
		mp[i].Draw();
	}
}
void SetMapEffectTex(int texNo) {
	mapTex = texNo;
}
void SetMapEffect(Float2 spawnPos, Float2* playerPos, int index) {
	
	for (int i = 0; i < EFFECT_MAX_CNT; i++)
	{
		if (!mp[i].isEnable()) {
			mp[i].Spawn(spawnPos, playerPos, (index + 1));
			break;
		}
	}
	

}