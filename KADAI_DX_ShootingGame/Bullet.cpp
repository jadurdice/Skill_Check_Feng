#include"Bullet.h"
#include"common.h"
#include "Game.h"
#include"GameMaster.h"
#include "Sprite.h"
#include"sound.h"
#include"Debug.h"
#include"Particle.h"

Bullet::Bullet()
{
	bulletAngle = 90;
	bulletMoveSpeed = DEFMOVSPD;

	bulletVelocity = { bulletMoveSpeed,0.0f };

	bulletCol.radius = 8;
	bulletDamege = 3;
}

void Bullet::BulletUpdate()
{
	if (!isEnable) {
		return;
	}

	//ムーブパターンをチェック

	MoveBullet();

	if (GetBoss()->thisMoveSet.no == EM_Boss2Center && (shootBy & ENM) && GetBoss()->GetEnemyEnable()) {
		
		SetParticle(P_Laser, bulletCol.pos, D3DCOLOR_RGBA(0, 255, 255, 255), 5, 1.0f, 0);
	}
	else if ((shootBy & ENM)) {
		SetParticle(P_Laser, bulletCol.pos, D3DCOLOR_RGBA(255, 128, 128, 255), 5, 0.4f, 0);
	}



	if (GameSystem::isOutGameZone(bulletPos.x, bulletPos.y)) {
		isEnable = false;
	}

	bulletCol.pos = { bulletPos.x + 8,bulletPos.y + 8 };
}

void Bullet::ShootThis(float x, float y, float angle, float speed)
{
	if (isEnable) {
		return;
	}



	isEnable = true;
	bulletPos = { x,y };

	D3DXVECTOR2 temp;
	float radian = DEGREE_TO_RADIAN(angle);

	bulletVelocity = { speed,0.0f };

	temp.x = bulletVelocity.x * cosf(radian) - bulletVelocity.y*sinf(radian);
	temp.y = bulletVelocity.x * sinf(radian) + bulletVelocity.y*cosf(radian);

	bulletVelocity = temp;




}

void Bullet::DrawBullet()
{

	DebugSetColor(D3DCOLOR_RGBA(255, 255, 0, 255));
	DebugDrawCircleCol(bulletCol.pos.x, bulletCol.pos.y, bulletCol.radius);

	if (shootBy & ENM) {
		SetColor(255, 100, 100, 255);
	}

	if (isEnable) {
		DrawSpriteRotPlg(
			bulletTexNo,
			bulletPos.x, bulletPos.y,
			0, 0,
			16, 16,
			bulletAngle,
			0.5f, 0.5f,
			2.0f, 2.0f
		);
	}
	SetColor(255, 255, 255, 255);
}

void Bullet::BulletDestroy()
{
	isEnable = false;
	bulletCol.pos = { 0.0f,0.0f };
}

int Bullet::GetBulletDmg()
{
	return bulletDamege;
}

void Bullet::MoveBullet()
{



	bulletPos.x += bulletVelocity.x;
	bulletPos.y += bulletVelocity.y;
}

CircleCol * Bullet::GetCollision()
{
	return &bulletCol;
}

bool Bullet::GetBulletEnable()
{
	return isEnable;
}





void Homing::BulletUpdate()
{
	if (!isEnable) {
		return;
	}

	if (GameSystem::isOutGameZone(bulletOldPos.x, bulletOldPos.y)) {
		BulletDestroy();
	}

	if (!GetEnableEnemy()) {
		BulletDestroy();
	}
	D3DXVECTOR2 bulletAcc = { 0.0f,0.0f };
	D3DXVECTOR2 distance = { targetPos->x - bulletPos.x,targetPos->y - bulletPos.y };


	//外力を足す
	float intToFloat = bulletLifeTime / 60.0f;

	if (bulletLifeTime < bulletStopTime) {
		bulletPos += bulletVelocity * DELTATIME* bulletSpeed;
	}
	else {
		D3DXVECTOR2 upper;
		float downer;

		upper = ((distance - bulletVelocity * intToFloat)*2.0f);
		downer = (intToFloat * intToFloat);

		bulletAcc = upper / downer;


		if (shootBy& ENM) {
			if (GameSystem::SqrMagnitude(bulletAcc.x, bulletAcc.y) > HOMINGFORCE) {
				GameSystem::Normalize(bulletAcc.x, bulletAcc.y);
				bulletAcc.x *= HOMINGFORCE;
				bulletAcc.y *= HOMINGFORCE;
			}

		}

		bulletLifeTime -= 1;

		bulletVelocity += bulletAcc * DELTATIME;
		bulletPos += bulletVelocity * DELTATIME * bulletSpeed;
	}




	bulletOldPos = {
		GameSystem::Lerp(bulletOldPos.x, bulletPos.x,DELTATIME),
		GameSystem::Lerp(bulletOldPos.y, bulletPos.y,DELTATIME)
	};

	if (shootBy&PLR) {
		SetParticle(P_Trace, bulletCol.pos, D3DCOLOR_RGBA(128,128,255, 255), 120, 0.3f, GameSystem::RelDegree({0.0f,0.0f}, bulletVelocity));

		for (int j = 0; j < B_Count; j++)
		{
			for (int i = 0; i < GetBulletMax(); i++)
			{
				if (!GetBullet(j, i)->GetBulletEnable() || GetBullet(j, i)->shootBy != ENM) {
					continue;
				}
				checkHoming2Bullet(this,GetBullet(j, i));
			}
		}

	}
	else {
		SetParticle(P_Trace, bulletCol.pos, D3DCOLOR_RGBA(255, 128, 64, 255), 120, 0.3f, GameSystem::RelDegree({ 0.0f,0.0f }, bulletVelocity));
	}

	bulletCol.pos = { bulletPos.x + 8,bulletPos.y + 8 };

}

void Homing::ShootThis(D3DXVECTOR2 insPos, D3DXVECTOR2 * target, int lifeTime, int stopTime, float speed)
{
	isEnable = true;
	bulletPos = insPos;
	bulletOldPos = bulletPos;

	bulletLifeTime = lifeTime + GameSystem::RandInt(-30, 30);
	bulletStopTime = stopTime + GameSystem::RandInt(-30, 30);
	int temp = GameSystem::RandInt(-135,135);
	bulletVelocity = { 
		200.0f * cosf(DEGREE_TO_RADIAN(temp)),
		200.0f*sinf((DEGREE_TO_RADIAN(temp)))};

	targetPos = target;

	bulletSpeed = speed;

	bulletCol.radius = 8;
	bulletDamege = 3;
}


void Homing::DrawBullet()
{
	if (!isEnable) {
		return;
	}

	DebugSetColor(D3DCOLOR_RGBA(255, 255, 0, 255));
	DebugDrawCircleCol(bulletCol.pos.x, bulletCol.pos.y, bulletCol.radius);

	if (shootBy & ENM) {
		SetColor(255, 100, 100, 255);
	}

	if (isEnable) {
		DrawSpriteRotPlg(
			bulletTexNo,
			bulletPos.x, bulletPos.y,
			0, 0,
			16, 16,
			0,
			0.5f, 0.5f,
			2.0f, 2.0f
		);
	}
	SetColor(255, 255, 255, 255);
}

bool isRound;

Bullet actBullet[BULLETMAX];
Homing actHoming[BULLETMAX];

void InitBullet()
{
	int a;
	a = TextureSetLoadFile("asset/texture/laser-bolts.png", 32, 32);

	for (int i = 0; i < BULLETMAX; i++)
	{
		actBullet[i].bulletTexNo = a;
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		actHoming[i].bulletTexNo = a;
	}
}
void UninitBullet()
{
	ClearBullet();
}
void UpdateBullet()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		actBullet[i].BulletUpdate();
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		actHoming[i].BulletUpdate();
	}

}
void DrawBullet()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (actBullet[i].isEnable) {
			actBullet[i].DrawBullet();
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		actHoming[i].DrawBullet();
	}

}

void BulletCreate(float insX, float insY, float angle, float speed, char shootBy)
{
	if (GetActionPlayer()->respawnCnt > 0 && (shootBy & ENM)) {
		return;
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!actBullet[i].isEnable) {
			actBullet[i].ShootThis(insX, insY, angle, speed);
			actBullet[i].shootBy = shootBy;
			break;
		}
	}

	if (!isRound && !(shootBy & PLR)) {
		if (GetBoss()->thisMoveSet.no == EM_Boss2Center && speed > 10.0f) {
			return;
		}
		PlaySound(SE_SHOT);
	}
}

void HomingCreate(D3DXVECTOR2 insPos, D3DXVECTOR2 * target, int lifeTime, int stopTime, float speed, char shootBy) {
	if (GetActionPlayer()->respawnCnt > 0 && (shootBy & ENM)) {
		return;
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!actHoming[i].isEnable) {
			actHoming[i].ShootThis(insPos, target, lifeTime, stopTime, speed);
			actHoming[i].shootBy = shootBy;
			break;
		}
	}
	PlaySound(SE_MISSILE);
}

void WayBulletCreate(D3DXVECTOR2 insPos, D3DXVECTOR2 targetPos, int value, int degree, float speed, char shootBy)
{
	//way弾の打ち方法
	//撃つ方向を決めて、基本角度を決める
	//展開角度を/2、基本角度をマイナスしておいとく、

	float shootDeg;
	if (targetPos == nullptr) {
		shootDeg = -90;
	}
	else {
		shootDeg = GameSystem::RelDegree(insPos, targetPos) - 0.5f*degree;
	}
	isRound = true;

	if (degree == 360) {
		float interval = degree / value;
		for (int i = 0; i < value; i++)
		{
			BulletCreate(insPos.x, insPos.y, shootDeg + interval * i, speed, shootBy);

		}
	}
	else {
		float interval = degree / (value - 1);

		for (int i = 0; i < value; i++)
		{
			BulletCreate(insPos.x, insPos.y, shootDeg + interval * i, speed, shootBy);

		}

	}
	isRound = false;
	if (!(shootBy & PLR)) {
		PlaySound(SE_SHOT);
	}
}


Bullet* GetBullet(int genre, int no) {
	switch (genre) {
	case B_Normal:
		return &actBullet[no];
	case B_Homing:
		return &actHoming[no];
	}

	return nullptr;
}
D3DXVECTOR2* GetNearestBullet() {
	float length;
	D3DXVECTOR2 sqr = { SCREEN_WIDTH,SCREEN_HEIGHT };
	D3DXVECTOR2 *target = nullptr;
	length = D3DXVec2LengthSq(&sqr);
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (actBullet[i].isEnable && (actBullet[i].shootBy & ENM)) {
			sqr = actBullet[i].GetCollision()->pos - GetActionPlayer()->GetCollision()->pos;
			if (length >= D3DXVec2LengthSq(&sqr)) {
				length = D3DXVec2LengthSq(&sqr);
				target = &actBullet[i].GetCollision()->pos;
			}
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (actHoming[i].isEnable && (actHoming[i].shootBy & ENM)) {
			sqr = actHoming[i].GetCollision()->pos - GetActionPlayer()->GetCollision()->pos;
			if (length >= D3DXVec2LengthSq(&sqr)) {
				length = D3DXVec2LengthSq(&sqr);
				target = &actHoming[i].GetCollision()->pos;
			}
		}
	}
	sqr = { SCREEN_WIDTH,SCREEN_HEIGHT };


	if (length != D3DXVec2LengthSq(&sqr)) {
		return target;
	}
	else {
		return nullptr;
	}

}

void ClearBullet() {
	for (int i = 0; i < BULLETMAX; i++)
	{
		actHoming[i].BulletDestroy();
		actBullet[i].BulletDestroy();
	}
}

int GetBulletMax() {
	return BULLETMAX;
}

