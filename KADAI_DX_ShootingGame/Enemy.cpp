#include"Enemy.h"
#include"Game.h"
#include"GameMaster.h"
#include"score.h"
#include"Particle.h"
#include"PhaseManeger.h"
#include"Item.h"
#include"Effect.h"
#include"Player.h"
#include"sound.h"
#include"Debug.h"

bool isBoss;
unsigned int bossSecTexNo;


Enemy::Enemy()
{
	thisMoveSet.angle = 0;
	enemyMoveSpeed = 2.0f;
	thisMoveSet.velocity = { 1.0f,1.0f };
	enemyCol.radius = 16;
	score = 300;
	hitPoint = 10;
}
void AttackSetting::Attack(D3DXVECTOR2 originPos)
{
	switch (no) {
	case EA_Straight: {
		float degree = GameSystem::RelDegree({ 0.0f,0.0f }, velocity);
		if (GameSystem::GetFrame() % interval == 0)BulletCreate(originPos.x, originPos.y, degree, speed, ENM);
		brlAngle = degree;
	}break;
	case EA_Player: {

		targetPos = &GetActionPlayer()->GetCollision()->pos;

		float degree = GameSystem::RelDegree(originPos, *targetPos);
		if (GameSystem::GetFrame() % interval == 0)BulletCreate(originPos.x, originPos.y, degree, speed, ENM);
		brlAngle = degree;

	}break;
	case EA_Sector:
	case EA_Round: {
		if (no == EA_Round) {
			angle = 360;
		}
		if ((GameSystem::GetFrame() + lifeTime) % interval == 0) {
			WayBulletCreate(originPos, *targetPos, value, angle, speed, ENM);
		}

		if (no == EA_Round) {
			angle = 90;
		}

		if (targetPos == nullptr) {
			return;
		}
		brlAngle = GameSystem::RelDegree(originPos, *targetPos);

	}break;
	case EA_Homing: {

		for (int i = 0; i < value; i++)
		{
			if (GameSystem::GetFrame() % interval == 0)HomingCreate(originPos, targetPos, lifeTime, stopTime, speed, ENM);
		}

		brlAngle = GameSystem::RelDegree(originPos, *targetPos);

	}break;
	case EA_Boss1Idle: {

		angle = 90;

	}break;
	case EA_Boss1Attack1: {

		angle = GameSystem::Lerp(
			angle,
			90.0f + -2.0*lifeTime * sinf(DEGREE_TO_RADIAN(value*0.3f)),
			DELTATIME
		);


		if (GameSystem::GetFrame() % interval == 0)
		{
			BulletCreate(originPos.x, originPos.y, angle - 90, min(speed, speed*-1.0f)*2.0f, ENM);
		}

		value += 1;

	}break;
	case EA_Boss1Attack2: {

		if ((GameSystem::GetFrame() + stopTime) % (interval) == 0)
		{
			angle = 180;
			WayBulletCreate({ originPos.x - 50.0f ,originPos.y }, { 0.0f,originPos.y }, value, angle, speed, ENM);
			value += 1;
			angle = 90;
		}


	}break;
	case EA_Boss1Attack3: {

		angle += value;

		D3DXVECTOR2 temp = { 0.0f,0.0f };

		temp.x = originPos.x + cosf(DEGREE_TO_RADIAN(angle));
		temp.y = originPos.y + sinf(DEGREE_TO_RADIAN(angle));

		if ((GameSystem::GetFrame()) % (interval) == 0)
		{
			WayBulletCreate({ originPos.x  ,originPos.y }, temp, abs(value), 360, speed, ENM);

		}


	}break;
	case EA_Boss2Idle: {

		angle = GameSystem::RelDegree(
			GetActionPlayer()->GetCollision()->pos,
			GetBoss()->GetCollision()->pos);

	}break;
	case EA_Boss2Right: {

		if (GameSystem::GetFrame() % interval == 0) {

			AttackSetting tempAttack;
			MoveSetting tempMove;

			
			tempAttack.targetPos = &GetActionPlayer()->GetCollision()->pos;
			tempAttack.no = EA_Round;
			tempAttack.angle = 360;
			tempAttack.interval = interval / 2;
			tempAttack.speed = speed*0.5f;
			tempAttack.value = value;
			tempMove.no = EM_BossShot;
			tempMove.velocity = {speed,0.0f};
			tempMove.angle = -90;
			EnemyCreate(originPos,tempAttack,tempMove);
		}

	}break;
	case EA_Boss2Down: {
		value += 1;

		angle = 90;

		if (GameSystem::GetFrame() % interval == 0) {
			if (value <= lifeTime) {
				BulletCreate(originPos.x, originPos.y, angle, speed, ENM);
				BulletCreate(originPos.x, originPos.y, angle - 15, speed, ENM);
				BulletCreate(originPos.x, originPos.y, angle + 15, speed, ENM);

				if (GetBoss()->hitPoint < 5500) {
					BulletCreate(originPos.x, originPos.y, angle - 30, speed, ENM);
					BulletCreate(originPos.x, originPos.y, angle + 30, speed, ENM);
				}

			}
			else {
				if (value > lifeTime + stopTime) {
					value = 0;
					if (stopTime > 0) {
						stopTime -= lifeTime;
					}
				}
			}

		}

	}break;
	case EA_Boss2Left: {
		value += lifeTime;

		angle = 
			GameSystem::RelDegree(originPos,GetActionPlayer()->GetCollision()->pos)
			+ stopTime * sinf(DEGREE_TO_RADIAN(value));

		angle += 180.0f;

		if (value > 360) {
			stopTime -= 15;
			value = 0;
		}

		if (GameSystem::GetFrame() % interval == 0) {
				BulletCreate(originPos.x, originPos.y, angle, speed, ENM);
		}

	}break;
	case EA_Boss2Up: {

		if (GameSystem::GetFrame() % interval == 0) {
			int tempSpeed = speed;
			for (; tempSpeed >= 1.0f;)
			{
				BulletCreate(originPos.x, originPos.y + 50.0f, angle - 180, tempSpeed, ENM);
				BulletCreate(originPos.x, originPos.y + 50.0f, angle - 195, tempSpeed, ENM);
				BulletCreate(originPos.x, originPos.y + 50.0f, angle - 165, tempSpeed, ENM);

				if (GetBoss()->hitPoint < 5500) {
					BulletCreate(originPos.x, originPos.y + 50.0f, angle - 210, tempSpeed, ENM);
					BulletCreate(originPos.x, originPos.y + 50.0f, angle - 150, tempSpeed, ENM);
				}

				tempSpeed *= 0.9f;
			}
		}

	}break;
	case EA_Boss2Center: {
		brlAngle += 90;
		if (value < 120) {
			value += 1;
		}
		else {
			BulletCreate(originPos.x, originPos.y, angle, -1.0f*speed, ENM);
			int bossHP = GetBoss()->hitPoint / 10;

			if (bossHP < 150 && GameSystem::GetFrame()%60 == 0) {
				WayBulletCreate(originPos, GetActionPlayer()->GetCollision()->pos, 5, 360, 1.0f, ENM);
			}

			bossHP = (300 - bossHP)/5;
			angle += DEGREE_TO_RADIAN(bossHP);



		}



	}break;
	}
	brlAngle -= 90;
}
void MoveSetting::Move(D3DXVECTOR2& originPos)
{

	switch (no) {
	case EM_Straight: {

		angle = GameSystem::RelDegree(originPos, (originPos + velocity)) - 90;

		originPos.x += velocity.x;
		originPos.y += velocity.y;

	}break;
	case EM_Path: {

		angle = GameSystem::RelDegree(originPos, pathPoint[period]) + 90;

		originPos = {
			GameSystem::Lerp(originPos.x,pathPoint[period].x,speed * DELTATIME),
			GameSystem::Lerp(originPos.y,pathPoint[period].y,speed * DELTATIME)

		};

		if (GameSystem::GetFrame() % moveLength == 0 && period != lastPoint) {
			period += 1;
		}

	}break;
	case EM_Homing: {


		if (period < 900) {


			angle = GameSystem::RelDegree(originPos, *targetPos) + 90;
			originPos = {
			GameSystem::Lerp(originPos.x, GetActionPlayer()->GetPlayerPos().x,speed * DELTATIME),
			GameSystem::Lerp(originPos.y, GetActionPlayer()->GetPlayerPos().y,speed * DELTATIME)
			};
			period += 1;
		}
		else {

			angle = 90;
			originPos = {
			GameSystem::Lerp(originPos.x, -0.5f*SCREEN_WIDTH,speed * DELTATIME),
			GameSystem::Lerp(originPos.y, originPos.y,speed * DELTATIME)
			};

		}
	}break;
	case EM_Boss1Intro: {
		angle = 90;

		originPos = {
			GameSystem::Lerp(originPos.x,  SCREEN_WIDTH*0.8f,speed * DELTATIME),
			originPos.y
		};

	}break;
	case EM_Boss1Move: {
		angle = 90;

		originPos = {
			GameSystem::Lerp(originPos.x,  SCREEN_WIDTH*0.8f,speed * DELTATIME),
			GameSystem::Lerp(originPos.y,SCREEN_HEIGHT*0.5f + 50.0f*sinf(DEGREE_TO_RADIAN(GameSystem::GetFrame())),speed*DELTATIME)
		};
	}break;
	case EM_Boss1Outro: {
		angle = 90;

		if (GameSystem::GetFrame() % 15 == 0) {
			D3DXVECTOR2 temp;
			float randAngle = GameSystem::RandFloat(0.0f, 360.0f);
			temp = {
				originPos.x + BROKEN_TEXW + BROKEN_TEXW * cosf(DEGREE_TO_RADIAN(randAngle)),
				originPos.y + BROKEN_TEXH + BROKEN_TEXH * sinf(DEGREE_TO_RADIAN(randAngle))
			};
			SetEffect(temp);
			PlaySound(SE_EXPLOSION);
		}

		originPos = {
			GameSystem::Lerp(originPos.x,  SCREEN_WIDTH*0.6f,speed * DELTATIME),
			originPos.y + GameSystem::RandInt(-5,5)
		};

	}break;
	case EM_Boss2Intro: {

		if (moveLength < 270) {
			moveLength += 1;
		}
		originPos = {
			GameSystem::Lerp(originPos.x,  SCREEN_WIDTH*0.8f + BOSS2_TEXW * sinf(DEGREE_TO_RADIAN(moveLength)),speed * DELTATIME),
			originPos.y
		};

	}break;
	case EM_Boss2Move: {

		originPos = {
			GameSystem::Lerp(originPos.x, pathPoint[0].x,speed * 1.0f / 90.0f),
			GameSystem::Lerp(originPos.y, pathPoint[0].y,speed * 1.0f / 90.0f)
		};

	}break;
	case EM_Boss2Right: {
		moveLength += 1;

		originPos = {
					originPos.x,
					GameSystem::Lerp(originPos.y,
					0.25f *SCREEN_HEIGHT + 0.5f*SCREEN_HEIGHT*sinf(DEGREE_TO_RADIAN(moveLength)),
					speed*DELTATIME)
		};



	}break;
	case EM_Boss2Down: {
		moveLength += 1;

		originPos = {
			GameSystem::Lerp(originPos.x,
			0.25f *SCREEN_WIDTH + 0.5f*SCREEN_WIDTH*sinf(DEGREE_TO_RADIAN(moveLength)),
			speed*DELTATIME),
			originPos.y
		};
	}break;
	case EM_Boss2Left: {
		moveLength += 1;

		originPos = {
			originPos.x,
			GameSystem::Lerp(originPos.y,
			0.25f *SCREEN_HEIGHT + 0.5f*SCREEN_HEIGHT*sinf(DEGREE_TO_RADIAN(moveLength)),
			speed*DELTATIME)

		};
	}break;
	case EM_Boss2Up: {
		moveLength += 1;

		originPos = {
			GameSystem::Lerp(originPos.x,
			0.25f *SCREEN_WIDTH + 0.5f*SCREEN_WIDTH*sinf(DEGREE_TO_RADIAN(moveLength)),
			speed*DELTATIME),
			originPos.y
		};

	}break;
	case EM_Boss2Center: {
		moveLength += 1;
		originPos = {
			GameSystem::Lerp(originPos.x,10.0f*cosf(DEGREE_TO_RADIAN(moveLength)) + SCREEN_WIDTH * 0.5f - 250.0f,speed*DELTATIME),
			GameSystem::Lerp(originPos.y,10.0f*sinf(DEGREE_TO_RADIAN(moveLength)) + SCREEN_HEIGHT * 0.5f - 250.0f,speed*DELTATIME)
		};
	}break;
	case EM_BossShot: {
		originPos = {
			originPos.x + velocity.x,
			originPos.y + velocity.y
		};
	}break;
	case EM_Boss2Outro: {
		angle = 0;

		if (GameSystem::GetFrame() % 15 == 0) {
			D3DXVECTOR2 temp;
			float randAngle = GameSystem::RandFloat(0.0f, 360.0f);
			temp = {
				originPos.x +BOSS2_TEXW* cosf(DEGREE_TO_RADIAN(randAngle)),
				originPos.y +BOSS2_TEXH* sinf(DEGREE_TO_RADIAN(randAngle))
			};
			SetEffect(temp);
			PlaySound(SE_EXPLOSION);
		}

		originPos = {
			GameSystem::Lerp(originPos.x,  SCREEN_WIDTH*0.6f,speed * DELTATIME),
			originPos.y + GameSystem::RandInt(-5,5)
		};

	}break;

	}

}
void Enemy::EnemyUpdate()
{
	if (!isEnable) {
		return;
	}

	//ムーブパターンをチェック
	thisMoveSet.Move(enemyPos);
	thisAttackSet.Attack(enemyCol.pos);
	if (damageFactor > 0) {
		damageFactor -= 1;
	}

	if (isEnteredGameZone) {
		if (GameSystem::isOutGameZone(enemyPos.x, enemyPos.y)) {
			isEnable = false;
		}
	}
	else {
		if (!GameSystem::isOutGameZone(enemyPos.x, enemyPos.y)) {
			isEnteredGameZone = true;
		}
	}


	enemyCol.pos = { enemyPos.x + 0.5f*ENM_RED_TEXW,enemyPos.y + 0.5f*ENM_RED_TEXH };
	brlPos = {
	 enemyPos.x + 0.35f*ENM_RED_TEXW,
	 enemyPos.y + 0.5f*ENM_RED_TEXW
	};


	CheckBullet();

}
void Enemy::SpawnThis(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move)
{
	if (isEnable) {
		return;
	}
	isEnable = true;
	isEnteredGameZone = false;
	enemyPos = { pos.x,pos.y };
	enemyCol.pos = { pos.x,pos.y };
	thisAttackSet = attack;
	thisMoveSet = move;
	hitPoint = thisAttackSet.hp;

}
void Enemy::DrawEnemy()
{

	if (isEnable) {
		SetColor(255, 255 - damageFactor * 20, 255 - damageFactor * 20, 255);

		switch (thisAttackSet.no) {
		case EA_Straight: {
			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				ENM_RED_TEXU, ENM_RED_TEXV,
				ENM_RED_TEXW, ENM_RED_TEXH,
				thisMoveSet.angle,
				0.5f, 0.5f,
				0.5f, 0.5f
			);

			DrawSpriteRotPlg(
				enemyTexNo,
				brlPos.x, brlPos.y,
				BRL_RED_TEXU, BRL_RED_TEXV,
				BRL_RED_TEXW, BRL_RED_TEXH,
				thisAttackSet.brlAngle,
				0.5f, 0.0f,
				0.5f, 0.5f
			);

		}break;
		case EA_Player: {
			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				ENM_SAND_TEXU, ENM_SAND_TEXV,
				ENM_SAND_TEXW, ENM_SAND_TEXH,
				thisMoveSet.angle,
				0.5f, 0.5f,
				0.5f, 0.5f
			);

			DrawSpriteRotPlg(
				enemyTexNo,
				brlPos.x, brlPos.y,
				BRL_SAND_TEXU, BRL_SAND_TEXV,
				BRL_RED_TEXW, BRL_RED_TEXH,
				thisAttackSet.brlAngle,
				0.5f, 0.0f,
				0.5f, 0.5f
			);

		}break;
		case EA_Sector: {
			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				ENM_BLUE_TEXU, ENM_BLUE_TEXV,
				ENM_BLUE_TEXW, ENM_BLUE_TEXH,
				thisMoveSet.angle,
				0.5f, 0.5f,
				0.5f, 0.5f
			);

			DrawSpriteRotPlg(
				enemyTexNo,
				brlPos.x, brlPos.y,
				BRL_BLUE_TEXU, BRL_BLUE_TEXV,
				BRL_RED_TEXW, BRL_RED_TEXH,
				thisAttackSet.brlAngle,
				0.5f, 0.0f,
				0.5f, 0.5f
			);

		}break;
		case EA_Round: {
			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				ENM_BIGRED_TEXU, ENM_BIGRED_TEXV,
				ENM_BIGRED_TEXW, ENM_BIGRED_TEXH,
				thisMoveSet.angle,
				0.5f, 0.5f,
				0.5f, 0.5f
			);

		}break;
		case EA_Homing: {
			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				ENM_DARK_TEXU, ENM_DARK_TEXV,
				ENM_DARK_TEXW, ENM_DARK_TEXH,
				thisMoveSet.angle,
				0.5f, 0.5f,
				0.5f, 0.5f
			);
		}break;

		}



	}
}
void Enemy::DamegeThis(int dmg)
{
	hitPoint -= dmg;
	damageFactor += 10;
	PlaySound(SE_DAMAGE);
	if (hitPoint <= 0) {
		EnemyDestroy();
		PlaySound(SE_EXPLOSION);
	}

}
void Enemy::EnemyDestroy()
{
	AddScore(score);
	SetEffect(enemyCol.pos);
	CheckItemGenre(enemyCol.pos);

	isEnable = false;
}
void Enemy::CheckBullet()
{
	for (int j = 0; j < B_Count; j++)
	{
		for (int i = 0; i < GetBulletMax(); i++)
		{
			if (!GetBullet(j, i)->GetBulletEnable() || GetBullet(j, i)->shootBy != PLR) {
				continue;
			}
			checkBullet2Enemy(GetBullet(j, i), this);
		}
	}
}
bool Enemy::GetEnemyEnable()
{
	return isEnable;
}
CircleCol* Enemy::GetCollision()
{
	return &enemyCol;
}
Enemy actEnemy[ENEMY_CNT_MAX];




const D3DXVECTOR2 turretDefPos[4] = {
{0.2f*BOSS_TEXW*4.0f - BOSS_TEXW * 1.5f,0.2f*BOSS_TEXH*4.0f - BOSS_TEXH * 1.7f},
{0.4f*BOSS_TEXW*4.0f - BOSS_TEXW * 1.5f,0.35f*BOSS_TEXH*4.0f - BOSS_TEXH * 1.7f},
{0.4f*BOSS_TEXW*4.0f - BOSS_TEXW * 1.5f,0.65f*BOSS_TEXH*4.0f - BOSS_TEXH * 1.7f},
{0.2f*BOSS_TEXW*4.0f - BOSS_TEXW * 1.5f,0.8f*BOSS_TEXH*4.0f - BOSS_TEXH * 1.7f}
};
class Turret :public Enemy {
private:
public:
	int no;

	Turret() {
		thisAttackSet.no = EA_Boss1Idle;
		score = 5000;
	}
	void	UpdateTurret();
	void	SetTurretPos(D3DXVECTOR2 setPos);
	void	DrawTurret();
};
class Boss :public Enemy {
private:

	bool toOutro;
public:
	int no;
	Turret rideOn[4];
	void	SetBossAM(AttackSetting atkSet, MoveSetting moveSet);
	void	InitBoss(int setNo);
	void	UpdateBoss();
	void	DrawBoss();
};
void Turret::UpdateTurret()
{

	if (no == 0) {
		enemyCol.pos = {
			enemyPos.x + TURRET_TEXW,
			enemyPos.y + TURRET_TEXH * 0.5f
		};

	}
	else {
		enemyCol.pos = {
			enemyPos.x + BOSS2_TEXW * 0.5f,
			enemyPos.y + BOSS2_TEXH * 0.5f
		};
	}
	if (damageFactor > 0) {
		damageFactor -= 1;
	}

	if (isEnable) {
		thisAttackSet.Attack(enemyCol.pos);
		CheckBullet();
	}

}
void Turret::SetTurretPos(D3DXVECTOR2 setPos)
{
	this->enemyPos = setPos;
}
void Turret::DrawTurret()
{
	if (no == 0) {
		if (isEnable) {
			SetColor(255, 255 - damageFactor * 20, 255 - damageFactor * 20, 255);

			DebugSetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			DebugDrawCircleCol(enemyCol.pos.x, enemyCol.pos.y, enemyCol.radius);

			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				TURRET_TEXU, TURRET_TEXV,
				TURRET_TEXW, TURRET_TEXH,
				thisAttackSet.angle,
				0.5f, 0.5f,
				2.5f, 2.5f);
			SetColor(255, 255, 255, 255);

		}
		else {

			DebugSetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			DebugDrawCircleCol(enemyCol.pos.x, enemyCol.pos.y, enemyCol.radius);

			DrawSpriteRotPlg(
				enemyTexNo,
				enemyPos.x, enemyPos.y,
				BROKEN_TEXU, BROKEN_TEXV,
				BROKEN_TEXW, BROKEN_TEXH,
				0,
				0.0f, 0.0f,
				1.0f, 1.0f);
			SetColor(255, 255, 255, 255);
		}

	}
	else {
		SetColor(255, 255 - damageFactor * 20, 255 - damageFactor * 20, 255);

		DebugSetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		DebugDrawCircleCol(enemyCol.pos.x, enemyCol.pos.y, enemyCol.radius);

		DrawSpriteRotPlg(
			enemyTexNo,
			enemyPos.x, enemyPos.y,
			1.0f* BOSS2_TEXW, 0,
			BOSS2_TEXW, BOSS2_TEXH,
			thisAttackSet.angle,
			0.5f, 0.5f,
			0.5f, 0.5f);
		SetColor(255, 255, 255, 255);
	}
}
void Boss::SetBossAM(AttackSetting atkSet, MoveSetting moveSet)
{
	if (no == 0) {
		this->thisMoveSet = moveSet;
		for (int i = 0; i < 4; i++)
		{
			rideOn[i].thisAttackSet = atkSet;
		}

	}
	if (no == 1) {
		this->thisMoveSet = moveSet;
		rideOn[0].thisAttackSet = atkSet;

	}
}
void Boss::InitBoss(int setNo)
{

	no = setNo;

	if (no == 0) {
		enemyPos = { SCREEN_WIDTH + BOSS_TEXW * 2.0f,0.5f*SCREEN_HEIGHT };

		isEnable = true;
		toOutro = false;

		PlaySound(SE_BOSS1SURROUND);

		thisMoveSet.angle = 90;
		damageFactor = 1;
		enemyCol.radius = 300.0f;

		for (int i = 0; i < 4; i++)
		{
			rideOn[i].isEnable = true;
			rideOn[i].no = 0;
			rideOn[i].enemyTexNo = enemyTexNo;
			rideOn[i].enemyCol.radius = 32.0f;
			rideOn[i].hitPoint = 2000;
		}
	}
	else {
		enemyPos = { SCREEN_WIDTH*0.6f,0.5f*(SCREEN_HEIGHT - BOSS2_TEXH) };

		damageFactor = 1;
		enemyTexNo = bossSecTexNo;

		toOutro = false;

		enemyCol.radius = BOSS2_TEXW * 0.2f;

		isEnable = true;

		rideOn[0].isEnable = true;
		rideOn[0].no = 1;
		rideOn[0].enemyTexNo = enemyTexNo;
		rideOn[0].enemyCol.radius = 64.0f;
		rideOn[0].hitPoint = 8000;


	}


}
void Boss::UpdateBoss()
{
	if (!isEnable) {
		return;
	}

	this->thisMoveSet.Move(enemyPos);

	if (no == 0) {
		enemyCol.pos = {
	enemyPos.x + BOSS_TEXW * 0.5f,
	enemyPos.y + BOSS_TEXH * 0.5f
		};




		if (thisMoveSet.no == EM_Boss1Outro) {
			if (damageFactor > 0) {
				damageFactor -= 1;
				if (damageFactor == 0) {
					damageFactor = 60;
				}
			}
		}
		if (!toOutro) {
			if (!GetAliveTurret()) {
				ForceBossOutro(0);
				toOutro = true;
			}
		}
		int add = 0;
		for (int i = 0; i < 4; i++)
		{

			rideOn[i].SetTurretPos((enemyPos)+turretDefPos[i]);
			rideOn[i].UpdateTurret();
			add += rideOn[i].hitPoint;
		}
		hitPoint = add;
	}
	else {

		if (GameSystem::GetFrame() % 6 == 0) {
			SetParticle(P_Dust, { enemyPos.x + BOSS2_TEXW * 0.25f,enemyPos.y + 0.3f*BOSS2_TEXH }, 0, 128, 1.0f, 0.0f);
			SetParticle(P_Dust, { enemyPos.x + BOSS2_TEXW * 0.25f,enemyPos.y + 0.7f*BOSS2_TEXH }, 0, 128, 1.0f, 0.0f);
		}

		if (!toOutro) {
			if (!GetAliveTurret()) {
				ForceBossOutro(1);
				ClearBullet();
				toOutro = true;
			}
		}


		hitPoint = rideOn[0].hitPoint;

		enemyCol.pos = {
	enemyPos.x + BOSS2_TEXW * 0.5f,
	enemyPos.y + BOSS2_TEXH * 0.5f
		};
		rideOn[0].SetTurretPos((enemyPos));
		rideOn[0].UpdateTurret();

	}




}
void Boss::DrawBoss()
{
	if (!isEnable) {
		return;
	}

	DebugSetColor(D3DCOLOR_RGBA(255, 255, 0, 255));

	DebugDrawCircleCol(enemyCol.pos.x, enemyCol.pos.y, enemyCol.radius);
	SetColor(255, 255 - damageFactor * 20, 255 - damageFactor * 20, 255);

	if (no == 0) {
		DrawSpriteRotPlg(
			enemyTexNo,
			enemyPos.x, enemyPos.y,
			BOSS_TEXU, BOSS_TEXV, BOSS_TEXW, BOSS_TEXH,
			thisMoveSet.angle, 0.5f, 0.5f, 4.0f, 4.0f
		);
		SetColor(255, 255, 255, 255);
		for (int i = 0; i < 4; i++)
		{
			rideOn[i].DrawTurret();
		}
	}
	else {
		DrawSpriteRotPlg(
			enemyTexNo,
			enemyPos.x, enemyPos.y,
			0, 0, BOSS2_TEXW, BOSS2_TEXH,
			thisMoveSet.angle, 0.5f, 0.5f, 0.5f, 0.5f
		);
		SetColor(255, 255, 255, 255);
		rideOn[0].DrawTurret();

	}


}

Boss	bossFirst;



void InitEnemy()
{
	int a;
	a = GetPlayerTex();
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		actEnemy[i].enemyTexNo = a;
	}
	bossFirst.enemyTexNo = a;
	bossSecTexNo = TextureSetLoadFile("asset/texture/boss2.png", 1182, 525);

}
void UninitEnemy()
{
	ClearEnemy();
	isBoss = false;
}
void UpdateEnemy()
{

	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		actEnemy[i].EnemyUpdate();
	}

	if (!isBoss) {
		return;
	}
	bossFirst.UpdateBoss();
}
void DrawEnemy()
{
	int enemyCnt = 0;
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (actEnemy[i].isEnable) {
			actEnemy[i].DrawEnemy();
			DebugSetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
			DebugDrawCircleCol(actEnemy[i].enemyCol.pos.x, actEnemy[i].enemyCol.pos.y, actEnemy[i].enemyCol.radius);

			enemyCnt += 1;
		}

	}

	if (!isBoss) {
		return;
	}
	bossFirst.DrawBoss();

	DebugFont_Draw(10.0f, 30.0f, "%d", enemyCnt);
}
void EnemyCreate(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move)
{
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!actEnemy[i].isEnable) {
			actEnemy[i].SpawnThis(pos, attack, move);
			break;
		}
	}
}
Enemy * GetEnemy(int no)
{
	return &actEnemy[no];
}
Enemy * GetEnableEnemy() {
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (actEnemy[i].isEnable) {
			return &actEnemy[i];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (bossFirst.rideOn[i].isEnable) {
			return &bossFirst.rideOn[i];
		}
	}

	return nullptr;
}
Enemy * GetNearestEnemy() {


	int index;
	float length;
	D3DXVECTOR2 sqr = { SCREEN_WIDTH,SCREEN_HEIGHT };
	length = D3DXVec2LengthSq(&sqr);

	if (isBoss) {
		for (int i = 0; i < 4; i++)
		{
			if (bossFirst.rideOn[i].isEnable) {
				sqr = bossFirst.rideOn[i].GetCollision()->pos - GetActionPlayer()->GetCollision()->pos;
				if (length >= D3DXVec2LengthSq(&sqr)) {
					length = D3DXVec2LengthSq(&sqr);
					index = i;
				}
			}
		}
		sqr = { SCREEN_WIDTH,SCREEN_HEIGHT };

		if (length != D3DXVec2LengthSq(&sqr)) {
			return &bossFirst.rideOn[index];
		}
		else {
			return nullptr;
		}
	}
	else {
		for (int i = 0; i < ENEMY_CNT_MAX; i++)
		{
			if (actEnemy[i].isEnable) {
				sqr = actEnemy[i].GetCollision()->pos - GetActionPlayer()->GetCollision()->pos;
				if (length >= D3DXVec2LengthSq(&sqr)) {
					length = D3DXVec2LengthSq(&sqr);
					index = i;
				}
			}
		}
		sqr = { SCREEN_WIDTH,SCREEN_HEIGHT };

		if (length != D3DXVec2LengthSq(&sqr)) {
			return &actEnemy[index];
		}
		else {
			return nullptr;
		}
	}




}
int GetEnemyCnt()
{
	int cnt = 0;
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!actEnemy[i].isEnable) {
			continue;
		}
		cnt += 1;
	}
	return cnt;
}

void ClearEnemy() {
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		actEnemy[i].EnemyDestroy();
	}
}




Enemy* GetBoss() {
	return &bossFirst;
}


void InitBoss(int no)
{
	isBoss = true;
	bossFirst.InitBoss(no);
}

void DestroyBoss(int no) {
	if (no == 0) {
		bossFirst.isEnable = false;
		AddScore(100000);
		ItemCreate({SCREEN_WIDTH,0.5f*SCREEN_HEIGHT}, I_1UP);
	}
	else {
		bossFirst.isEnable = false;
		AddScore(500000);
	}
}

void SetBossAM(AttackSetting atkSet, MoveSetting moveSet) {
	if (isBoss) {
		bossFirst.SetBossAM(atkSet, moveSet);
	}
}
void SetTurretA(AttackSetting atkSet, int no) {
	if (isBoss) {
		bossFirst.rideOn[no].thisAttackSet = atkSet;
	}
}
bool GetAliveTurret() {
	for (int i = 0; i < 4; i++)
	{
		if (bossFirst.rideOn[i].isEnable) {
			return true;
		}
	}
	return false;
}