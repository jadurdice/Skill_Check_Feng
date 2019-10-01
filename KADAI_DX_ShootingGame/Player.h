#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include "Game.h"
#include "Collision.h"
//#include "common.h"
//#include "input.h"
//#include "texture.h"
//#include "sprite.h"
//#include "Bullet.h"


class Player
{

public:
	unsigned int	playerTexNo;
	D3DXVECTOR2		playerPos;
	D3DXVECTOR2		playerScale;
	D3DXVECTOR2		playerVelocity;
	D3DXVECTOR2		muzzlePos;
	float			playerAngle;
	float			playerOldAngle;
	float			playerMaxAngle;

	D3DXVECTOR2		brlPos;
	float			barrelAngle;

	float			playerFireAngle;

	char			playerMoveState;

	int				shootInv;
	int				lastShoot;
	int				power;

	CircleCol		playerCol;

	int				frameCnt;
	int				respawnCnt;

	bool			enable;
	bool			inputPossible;
	bool			stageEnd;

	float			playerMoveSpeed;
	D3DXVECTOR2			texStaticScale;

	unsigned int GetPlayerTexNo();
	D3DXVECTOR2 GetPlayerPos();
	D3DXVECTOR2 GetPlayerScale();

	void SetPlayerTex(unsigned int texNo);
	void SetPlayerVelocity(D3DXVECTOR2 velocity);
	void SetPlayerPos(D3DXVECTOR2 pos);
	void SetPlayerScale(D3DXVECTOR2 scale);
	void MovePlayer();
	void PlayerDestroy();
	void DamegeCheck();
	void ItemCheck();

	CircleCol *GetCollision();
	int GetPower();
	int GetRawPower();
	void SetPower(int addNum);
	int GetLife();
	void SetLife(int addNum);
	int GetMissileNow();
	int GetMissileMax();
	void SetMissile(int addNum);


	void PlayerInit();
	void PlayerInput();
	void PlayerUpdate();
	void PlayerDraw();
	void ShootMissile();
	

private:
	int life;
	bool isShootMissile;
	int missileCnt;
	int missileInverse;
	int lastMissileCnt;
	int missileNow;
	int missileMax;

};


#define RESPAWNDEF		(360)
#define MISSILEINVDEF	(60)
#define MISSILEMAXDEF	(20)
#define MISSILEPERFRAME	(5)

#define PLRTEXW		(76.0f)
#define PLRTEXH		(72.0f)
#define PLRTEXU		(520)
#define PLRTEXV		(622)

//Body
// height="72" width="76" y="622" x="520" 

#define BRLTEXW		(24.0f)
#define BRLTEXH		(60.0f)
#define BRLTEXU		(720)
#define BRLTEXV		(640)

//Barrel
//height="60" width="24" y="640" x="720" name="tankGreen_barrel3_outline.png"/>


#define SIZEADJUST	(0.75f)

#define PLRDEFSPD	(4.5f)
#define ROTSPD		(3.0f)
#define PLRANGLEDEF	()

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
Player *GetActionPlayer();
int GetPlayerTex();

#endif