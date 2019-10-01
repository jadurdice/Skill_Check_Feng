#include"common.h"
#include "Game.h"
#include "Sprite.h"
#include"Debug.h"
#include"BackGround.h"
#include"sound.h"
#include"texture.h"
#include"Enemy.h"
#include"PhaseManeger.h"
#include"score.h"
#include "Item.h"

int itemCnt;


void Item::SetItem(D3DXVECTOR2 setPos, int setGenre)
{
	isEnable = true;
	genre = setGenre;
	pos = setPos;
	col.radius = 2.0f*defScale;
}

void Item::SetTexNo(int tex)
{
	texNo = tex;
}

void Item::UpdateItem()
{
	if (GameSystem::isOutGameZone(pos.x, pos.y)) {
		ItemDestroy();
	}

	pos.x -= 2.0f;
	scale = 0.75f*(1.0f + 0.1f*(sinf(DEGREE_TO_RADIAN(3*GameSystem::GetFrame()))));
	col.pos = { pos.x + 0.5f*defScale,pos.y + 0.5f*defScale };
	col.radius = 2.0f*defScale * (1.0f + 0.1f*(sinf(DEGREE_TO_RADIAN(3 * GameSystem::GetFrame()))));
}

void Item::DrawItem()
{
	DebugSetColor(D3DCOLOR_RGBA(0, 255,0, 255));
	DebugDrawCircleCol(col.pos.x, col.pos.y, col.radius);


	float uNow = genre * 0.167f * 353;
	DrawSpriteRotCenter(
		texNo,
		pos.x, pos.y,
		uNow, 0,
		0.167 * 353, 61,
		0, 0.0f, 0.0f,
		scale,scale
	);
}

void Item::PickUpThis()
{

	switch (genre)
	{
	case I_ScoreS:
		PlaySound(SE_DECIDE);
		AddScore(100);
		break;
	case I_ScoreM:
		PlaySound(SE_DECIDE);
		AddScore(500);
		break;
	case I_ScoreL:
		PlaySound(SE_DECIDE);
		AddScore(2000);
		break;
	case I_Power:
		PlaySound(SE_ITEMGET);
		GetActionPlayer()->SetPower(5);
		break;
	case I_Missile:
		PlaySound(SE_ITEMGET);
		GetActionPlayer()->SetMissile(5);
		break;
	case I_1UP:
		PlaySound(SE_ITEMGET);
		GetActionPlayer()->SetLife(1);
		break;
	default:
		return;
	}

	ItemDestroy();
}

void Item::ItemDestroy()
{
	isEnable = false;
}

CircleCol * Item::GetCollision()
{
	return &col;
}

bool Item::GetItemEnable()
{
	return isEnable;
}

int Item::GetItemGenre()
{
	return genre;
}

static Item actItem[ITEMMAX];
unsigned int itemTex;

void InitItem() {
	itemTex = TextureSetLoadFile("asset/texture/item.png",353,61);

	for (int i = 0; i < ITEMMAX; i++)
	{
		actItem[i].SetTexNo(itemTex);
	}
}
void UninitItem() {
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (!actItem[i].GetItemEnable()) {
			continue;
		}

		actItem[i].ItemDestroy();
	}

}
void UpdateItem() {
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (!actItem[i].GetItemEnable()) {
			continue;
		}
		actItem[i].UpdateItem();
	}
}
void DrawItem() {
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (!actItem[i].GetItemEnable()) {
			continue;
		}
		actItem[i].DrawItem();
	}
}
Item* GetItem(int no) {
	return &actItem[no];
}
void ItemCreate(D3DXVECTOR2 ins, int genre) {
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (actItem[i].GetItemEnable()) {
			continue;
		}
		actItem[i].SetItem(ins, genre);
		break;
	}
}

void CheckItemGenre(D3DXVECTOR2 ins) {

	if (GetActionPlayer()->GetRawPower() < (GetPhaseNow()*5.0f) && GetGenreValue(I_Power) < 5) {
		ItemCreate(ins, I_Power);
		return;
	}

	if (GetActionPlayer()->GetMissileMax() < (GetPhaseNow()*2.5f) && GetGenreValue(I_Missile) < 5) {
		ItemCreate(ins, I_Missile);
		return;
}

	if (GetEnemyCnt() < 4) {
		ItemCreate(ins, I_ScoreL);
		return;
	}

	ItemCreate(ins, GameSystem::RandInt(0, 1));
	return;
}

int GetGenreValue(int genre) {
	int cnt = 0;
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (!actItem[i].GetItemEnable() && actItem[i].GetItemGenre() != genre) {
			continue;
		}
		cnt += 1;
	}
	return cnt;
}