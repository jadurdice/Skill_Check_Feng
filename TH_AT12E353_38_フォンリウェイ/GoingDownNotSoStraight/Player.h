#pragma once



#include"AABB.h"

class Player : public MovingObject
{

public:

	const float cWalkSpeed = 50.0f;
	const float cJumpSpeed = -100.0f;
	const float cMinJumpSpeed = -50.0f;
	const float cMoveInAirMultiple = 0.8f;
	const float cHalfSizeY = 26.0f;
	const float cHalfSizeX = 7.0f;

	int jumpCnt = 2;

	enum CharacterState
	{
		Stand,
		Walk,
		Jump,
	};

	CharacterState mCurrentState = Stand;
	float mJumpSpeed;
	float mWalkSpeed;

	unsigned int	texNo;

	int				frameCnt;
	bool			enable;
	

	float			playerMoveSpeed;
	Float2			texStaticScale;
	Float2			velocity;

	unsigned int GetPlayerTexNo();
	Float2	GetPlayerPos();
	Float2	GetVelocity();
	int GetRoomInPack(int index);
	void SetPlayerTex(unsigned int setTexNo);
	void SetPlayerPos(Float2 nextPos);

	void PlayerDestroy();

	Player();
	void PlayerUpdate();
	void PlayerDraw();

	void AddRoomToPack(int index,int value);
	void RespawnStart();
	void GameoverStart();

	void Reset();

protected:
	int nowJumpCnt;
	int jumpFrame;

private:
	char playerMoveState;
	int roomInPack[11];
	int gameoverCnt;
	int respawnCnt;

};



#define PLRMOVRIGHT				(1<<1)
#define PLRMOVLEFT				(1<<0)

#define PLRDEFSPD		(10.0f)
#define PLRJUMPFORCE	(75.0f)
#define MAXFALLING		(100.0f)
#define MAXCIRCLE		(100.0f)
#define	RESPAWNDEFCNT	(120)


#define COLHOSEIX	(25.0f)
#define COLHOSEIY	(15.0f)

#define MAX_PAT (8)
#define PAT_SPD (5.0f)

void InitPlayer(int condi);
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
Player *GetActionPlayer();
void GetRoomInPack(int roomSent[11]);
void SetRoomInPack(int index, int value);

Float2 GetPlayerVelocity();


unsigned int GetPlayerTex();

int GetAllRoomCount();

void ResetPlayer();