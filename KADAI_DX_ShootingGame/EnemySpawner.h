#ifndef _ENEMYSPAWNER_H_
#define _ENEMYSPAWNER_H_

#include"common.h"

#define SPN_MAX	(32)

class EnemySpawner
{
public:
	bool enable;
	void SetSpawner(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move, int interval);
	void UpdateSpawner();


	void CleanSpawner();

private:
	Enemy spawnEnemy;
	D3DXVECTOR2 spnPos;
	D3DXVECTOR2 spnVelocity;
	int spnEnemyNo;
	int spnInterval;
	int checkFrame;


	
};
void UnInitEnemySpawner();
void UpdateEnemySpawner();

void SetSpawner(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move, int interval);
void CleanUp();

#endif