#pragma once

#include"AABB.h"

#define ENEMY_CNT_MAX	(128)
#define MAX_PAT_ENEMY	(2)

#define	HOMINGFORCE		(7.0f)
#define HOMINGTRY		(10.0f)
#define	DESTROYFRAME	(10)

#define MOVELEFT		(1<<0)
#define MOVERIGHT		(1<<1)

class Enemy:public MovingObject
{
public:

	unsigned int	enemyTexNo;
	float			enemyMoveSpeed;

	AABB	eAABB;
	
	float	lifeTime;
	int		destroyCnt;

	void	EnemyUpdate();
	void	SpawnThis(Float2 pos);
	void	DrawEnemy();
	void	EnemyDestroy();

	bool	isEnable;
	bool	GetEnemyEnable();
	AABB*	GetAABB();
	char	moveState;

};

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void ClearEnemy();

void EnemyCreate(Float2 pos);
Enemy* GetEnemy(int no);

void EnemySpawn();
void EnemySpawnTutor();

