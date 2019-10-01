#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ENEMY_CNT_MAX	(128)
#define MAX_PAT_ENEMY	(2)


#include"Collision.h"
#include "Game.h"
#include "common.h"
#include"Bullet.h"
#include "Player.h"

enum MoveType
{
	EM_Straight = 0,
	EM_Path,
	EM_Homing,
	EM_Boss1Intro,
	EM_Boss1Move,
	EM_Boss1Idle,
	EM_Boss1Outro,
	EM_Boss2Intro,
	EM_Boss2Move,
	EM_Boss2Right,
	EM_Boss2Down,
	EM_Boss2Left,
	EM_Boss2Up,
	EM_Boss2Center,
	EM_Boss2Outro,
	EM_BossShot,
	EM_Count
};
enum AttackType
{
	EA_Straight = 0,
	EA_Player,
	EA_Sector,
	EA_Round,
	EA_Homing,
	EA_Boss1Idle,
	EA_Boss1Attack1,
	EA_Boss1Attack2,
	EA_Boss1Attack3,
	EA_Boss2Idle,
	EA_Boss2Right,
	EA_Boss2Down,
	EA_Boss2Left,
	EA_Boss2Up,
	EA_Boss2Center,

	EA_Count
};

class AttackSetting {
public:
	int no;
	float speed;
	int interval;
	//直線、プレイヤー用
	D3DXVECTOR2 velocity;
	//扇状、円形用
	float angle;
	int value;
	//ホーミング用
	D3DXVECTOR2* targetPos;
	int lifeTime;
	int stopTime;

	float brlAngle;
	int hp;
	void Attack(D3DXVECTOR2 originPos);
};




class MoveSetting {

public:


	int no;
	float speed;
	float	angle;
	//直線用
	D3DXVECTOR2 velocity;
	//パス用
	int moveLength;
	int period;
	int lastPoint;
	D3DXVECTOR2 pathPoint[16];
	//ホーミング用
	D3DXVECTOR2* targetPos;

	void Move(D3DXVECTOR2 &originPos);
};



class Enemy
{
public:
	Enemy();

	unsigned int	enemyTexNo;
	D3DXVECTOR2		enemyPos;
	D3DXVECTOR2		brlPos;
	float			enemyMoveSpeed;

	CircleCol		enemyCol;

	int				hitPoint;

	int		score;

	int		spawnFrame;
	int		damageFactor;

	void	EnemyUpdate();
	void	SpawnThis(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move);
	void	DrawEnemy();
	void	DamegeThis(int dmg);
	void	EnemyDestroy();
	void	CheckBullet();

	bool	isEnable;
	bool	isEnteredGameZone;
	bool	GetEnemyEnable();
	CircleCol*	GetCollision();

	MoveSetting thisMoveSet;
	AttackSetting thisAttackSet;

};


//<SubTexture height = "60" width = "24" y = "371" x = "744" name = "tankRed_barrel3_outline.png" / >

#define ENM_RED_TEXW		(76.0f)
#define ENM_RED_TEXH		(80.0f)
#define ENM_RED_TEXU		(520)
#define ENM_RED_TEXV		(268)

#define BRL_RED_TEXW		(24.0f)
#define BRL_RED_TEXH		(60.0f)
#define BRL_RED_TEXU		(744)
#define BRL_RED_TEXV		(371)

#define ENM_BLUE_TEXW		(84.0f)
#define ENM_BLUE_TEXH		(84.0f)
#define ENM_BLUE_TEXU		(434)
#define ENM_BLUE_TEXV		(0)
#define BRL_BLUE_TEXU		(722)
#define BRL_BLUE_TEXV		(259)

#define ENM_SAND_TEXW		(84.0f)
#define ENM_SAND_TEXH		(80.0f)
#define ENM_SAND_TEXU		(439)
#define ENM_SAND_TEXV		(84)
#define BRL_SAND_TEXU		(745)
#define BRL_SAND_TEXV		(0)



#define ENM_BIGRED_TEXW		(104.0f)
#define ENM_BIGRED_TEXH		(104.0f)
#define ENM_BIGRED_TEXU		(240)
#define ENM_BIGRED_TEXV		(392)


//<SubTexture height = "92" width = "84" y = "426" x = "348" name = "tank_dark.png" / >

#define ENM_DARK_TEXW		(84.0f)
#define ENM_DARK_TEXH		(92.0f)
#define ENM_DARK_TEXU		(348)
#define ENM_DARK_TEXV		(426)


//<SubTexture height = "144" width = "124" y = "508" x = "0" name = "tankBody_huge_outline.png" / >
#define BOSS_TEXW		(124.0f)
#define BOSS_TEXH		(144.0f)
#define BOSS_TEXU		(0)
#define BOSS_TEXV		(508)

//<SubTexture height="52" width="36" y="72" x="652" name="specialBarrel1_outline.png"/>
#define TURRET_TEXW		(36.0f)
#define TURRET_TEXH		(52.0f)
#define TURRET_TEXU		(652)
#define TURRET_TEXV		(72)

//<SubTexture height="100" width="100" y="496" x="248" name="oilSpill_large.png"/>
#define BROKEN_TEXW		(99.0f)
#define BROKEN_TEXH		(99.0f)
#define BROKEN_TEXU		(249)
#define BROKEN_TEXV		(497)

//<SubTexture height = "144" width = "124" y = "508" x = "0" name = "tankBody_huge_outline.png" / >
#define BOSS2_TEXW		(591.0f)
#define BOSS2_TEXH		(525)




void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void EnemyCreate(D3DXVECTOR2 pos, AttackSetting attack, MoveSetting move);
Enemy* GetEnemy(int no);
Enemy * GetEnableEnemy();
Enemy * GetNearestEnemy();
int GetEnemyCnt();
void ClearEnemy();

void InitBoss(int no);
Enemy* GetBoss();
void DestroyBoss(int no);
void SetBossAM(AttackSetting atkSet, MoveSetting moveSet);
void SetTurretA(AttackSetting atkSet, int no);
bool GetAliveTurret();
#endif