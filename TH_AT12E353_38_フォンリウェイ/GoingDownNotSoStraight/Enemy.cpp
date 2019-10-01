#include"Enemy.h"
#include"Game.h"
#include"Player.h"
#include"sprite.h"
#include"complex"
#include"sound.h"

Float2 spawnPoint[8] = {
{ SCREEN_WIDTH*0.25f,-64.0f},
{ SCREEN_WIDTH*0.75f,-64.0f},
{ SCREEN_WIDTH*0.25f,SCREEN_HEIGHT + 64.0f },
{ SCREEN_WIDTH*0.75f,SCREEN_HEIGHT + 64.0f},
{ -64.0f,SCREEN_HEIGHT*0.25f},
{ -64.0f,SCREEN_HEIGHT*0.75f},
{ SCREEN_WIDTH + 64.0f,SCREEN_HEIGHT*0.25f },
{ SCREEN_WIDTH + 64.0f,SCREEN_HEIGHT*0.75f },
};

void Enemy::EnemyUpdate()
{
	if (!isEnable) {
		return;
	}



	if (destroyCnt != -1) {
		destroyCnt -= 1;
		if (destroyCnt == 0) {
			isEnable = false;
		}
	}
	else {
		if (isNowTutor()) {
			moveState = MOVELEFT;
			return;
		}
		Float2 upper, acceleration, distance;
		float downer;

		distance = MakeFloat2(
			pos.x - GetActionPlayer()->GetPlayerPos().x,
			pos.y - GetActionPlayer()->GetPlayerPos().y
		);


		upper.x = ((distance.x - speed.x * lifeTime)*2.0f);
		upper.y = ((distance.y - speed.y * lifeTime)*2.0f);
		downer = (lifeTime * lifeTime);

		acceleration = MakeFloat2(upper.x / downer, upper.y / downer);

		if (GameSystem::SqrMagnitude(acceleration.x, acceleration.y) > HOMINGFORCE) {
			GameSystem::Normalize(acceleration.x, acceleration.y);
			acceleration.x *= HOMINGFORCE;
			acceleration.y *= HOMINGFORCE;
		}

		lifeTime -= DELTATIME;
		speed = MakeFloat2(
			speed.x + acceleration.x * DELTATIME,
			speed.y + acceleration.y * DELTATIME);
		pos = MakeFloat2(
			pos.x - speed.x * DELTATIME,
			pos.y - speed.y * DELTATIME
		);

		if (speed.x > 0) {
			moveState = MOVELEFT;
		}
		else {
			moveState = MOVERIGHT;
		}

		if (lifeTime <= 0.0f) {
			lifeTime = HOMINGTRY;
		}

		eAABB.center = pos;

		if (eAABB.isOverlap(GetActionPlayer()->mAABB) && GetActionPlayer()->isCollisionToOther) {
			ClearEnemy();
			GetActionPlayer()->GameoverStart();

		}
	}




}
void Enemy::SpawnThis(Float2 spawnPos)
{

	isEnable = true;
	pos = spawnPos;
	speed = MakeFloat2(0.0f, 0.0f);
	eAABB.SetAABB(MakeFloat2(spawnPos.x, spawnPos.y + 32.0f), MakeFloat2(32.0f, 32.0f));
	lifeTime = HOMINGTRY;
	destroyCnt = -1;
}

void Enemy::DrawEnemy()
{
	float uNow, vNow;
	uNow = 0.0f;
	vNow = 5.0f*0.125f;

	if (destroyCnt != -1) {
		SetColor(255, 255, 255, (destroyCnt * (255 / DESTROYFRAME)));
	}

	DrawSpriteMove(
		enemyTexNo,
		pos.x, pos.y,
		uNow, vNow,
		0.125f, 0.125f, 64.0f, 64.0f, moveState);
	SetColor(255, 255, 255, 255);
}

void Enemy::EnemyDestroy()
{
	destroyCnt = DESTROYFRAME;
}

bool Enemy::GetEnemyEnable()
{
	return isEnable;
}

Enemy actEnemy[ENEMY_CNT_MAX];

void InitEnemy()
{
	int a;
	a = GetPlayerTex();
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		actEnemy[i].enemyTexNo = a;
	}

	//actEnemy[0].SpawnThis(MakeFloat2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f));

}
void UninitEnemy()
{

}
void UpdateEnemy()
{

	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		actEnemy[i].EnemyUpdate();
	}

}
void DrawEnemy()
{
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!actEnemy[i].isEnable) {
			continue;
		}

		actEnemy[i].DrawEnemy();

	}
}

void EnemyCreate(Float2 pos)
{
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!actEnemy[i].isEnable) {
			actEnemy[i].SpawnThis(pos);

			break;
		}
	}
}

Enemy * GetEnemy(int no)
{
	return &actEnemy[no];
}

void ClearEnemy() {
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!actEnemy[i].isEnable) {
			continue;
		}
		actEnemy[i].EnemyDestroy();
	}
}

void EnemySpawn() {
	EnemyCreate(spawnPoint[GameSystem::RandInt(0, 7)]);
	PlaySE(S_ENEMY);
}

void EnemySpawnTutor() {
	EnemyCreate(MakeFloat2(0.75f*SCREEN_WIDTH,0.25f*SCREEN_HEIGHT));
	EnemyCreate(MakeFloat2(0.75f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT));
	EnemyCreate(MakeFloat2(0.75f*SCREEN_WIDTH,0.75f*SCREEN_HEIGHT));
}
