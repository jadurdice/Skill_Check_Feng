#include"Enemy.h"
#include"sound.h"
#include"EnemySpawner.h"

static int glbSpawnCnt = 0;

EnemySpawner actSpawner[SPN_MAX];

void EnemySpawner::SetSpawner(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move, int interval)
{
	enable = true;
	spnPos = pos;
	spnInterval = interval;
	checkFrame = GameSystem::GetFrame();
	spawnEnemy.thisAttackSet = attack;
	spawnEnemy.thisMoveSet = move;
	EnemyCreate(spnPos, spawnEnemy.thisAttackSet, spawnEnemy.thisMoveSet);
}

void EnemySpawner::UpdateSpawner()
{
	int nowFrame = GameSystem::GetFrame();
	if (nowFrame > spnInterval + checkFrame) {
		checkFrame += spnInterval;
		EnemyCreate(spnPos, spawnEnemy.thisAttackSet, spawnEnemy.thisMoveSet);
	}
}

void EnemySpawner::CleanSpawner()
{
	enable = false;
	spnPos = { 0.0f,0.0f };
	spnVelocity = { 0.0f,0.0f };
	spnEnemyNo = 0;
	spnInterval = 0;
}

void UnInitEnemySpawner() {
	CleanUp();
}

void UpdateEnemySpawner()
{
	for (int i = 0; i < SPN_MAX; i++)
	{
		if (!actSpawner[i].enable) {
			continue;
		}
		actSpawner[i].UpdateSpawner();
	}
}

void SetSpawner(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move, int interval)
{
	for (int i = 0; i < SPN_MAX; i++)
	{
		if (!actSpawner[i].enable) {
			actSpawner[i].SetSpawner(pos,attack,move,interval);
			break;
		}
	}

	PlaySound(SE_ENEMYSPAWN);
}

void CleanUp() {
	for (int i = 0; i < SPN_MAX; i++)
	{
		if (!actSpawner[i].enable) {
			continue;
		}
		actSpawner[i].CleanSpawner();
	}
}