
#include"KeyMap.h"
#include"Player.h"
#include"Game.h"
#include"sprite.h"
#include"texture.h"
#include"StageManeger.h"
#include"main.h"
#include"SenceManeger.h"
#include"MapObject.h"
#include"complex"
#include"sound.h"

Player::Player() {

	Float2 startSize = { 64.0f, 64.0f };
	Float2 startPos = BORNPOS;

	texStaticScale = startSize;

	isCollisionToOther = true;

	mAABB.center = startPos;
	pos = startPos;
	mAABB.halfScale = MakeFloat2(cHalfSizeX, cHalfSizeY);
	mAABBOffset = mAABB.halfScale;

	mJumpSpeed = cJumpSpeed;
	mWalkSpeed = cWalkSpeed;

	playerMoveState = PLRMOVLEFT;

	enable = true;

	playerMoveSpeed = PLRDEFSPD;

}


unsigned int Player::GetPlayerTexNo() {
	return texNo;
}

Float2 Player::GetPlayerPos()
{
	return pos;
}

Float2 Player::GetVelocity()
{
	return speed;
}

int Player::GetRoomInPack(int index)
{
	return roomInPack[index];
}


void Player::SetPlayerTex(unsigned int setTexNo) {
	texNo = setTexNo;
}

void Player::SetPlayerPos(Float2 nextPos)
{
	pos = nextPos;
}


void Player::PlayerDestroy()
{
	enable = false;
}


void Player::PlayerUpdate() {

	if (GetSceneIndex() == S_Title) {
		pos.x = MIN(pos.x, SCREEN_WIDTH);
		pos.x = MAX(pos.x, 0.0f);
		pos.y = MIN(pos.y, SCREEN_HEIGHT);
		pos.y = MAX(pos.y, 0.0f);
	}


	if (!isCollisionToOther) {
		if (respawnCnt >= 0) {
			respawnCnt -= 1;
			if (respawnCnt == RESPAWNDEFCNT / 2) {
				Respawn();
			}
		}
		if (gameoverCnt > RESPAWNDEFCNT / 2) {
			gameoverCnt -= 1;
			if (gameoverCnt == RESPAWNDEFCNT / 2) {
				SceneChange(S_GameOver);
			}
		}
		UpdatePhysics();
		return;
	}

	
	switch (mCurrentState)
	{
	case Stand:
		speed = MakeFloat2(0.0f, 0.0f);
		if (!isOnGround)
		{
			nowJumpCnt += 1;
			mCurrentState = Jump;
			break;

		}
		if (KeyState(K_Right) != KeyState(K_Left))
		{
			mCurrentState = Walk;
			break;
		}
		else if ((Pressed(K_Jump)||Pressed(K_Attack)))
		{
			nowJumpCnt += 1;
			PlaySE(S_JUMP);
			speed.y = mJumpSpeed;
			mCurrentState = Jump;
			jumpFrame = 5;
			break;
		}
		if (KeyState(K_Down))
		{
			if (isOnOneWayPlatform) {
				pos.y += cOneWayPlatformThreshold;
				isOnOneWayPlatform = false;
				isThroughOneWay = true;
				mCurrentState = Jump;
			}

		}
		if (Pressed(K_Up)) {
			Float2 temp = GetGameMap()->GetMapTileAtPoint(oldPos);

		

			if (GetGameMap()->GetTile(temp.x, temp.y) == Box) {
				PlaySE(S_OPENBOX);
				GetNewRoomToPack();

			}

			if (GetGameMap()->GetTile(temp.x, temp.y) == NextD) {
				NextStage();
			}
		}

		break;
	case Walk:
		if (KeyState(K_Left) == KeyState(K_Right))
		{
			mCurrentState = Stand;
			speed = MakeFloat2(0.0f, 0.0f);
			break;
		}
		else if (KeyState(K_Right))
		{
			if (isPushesWallR)
				speed.x = 0.0f;
			else
				speed.x = mWalkSpeed;

		}
		else if (KeyState(K_Left))
		{
			if (isPushesWallL) {
				speed.x = 0.0f;

			}
			else {
				speed.x = -mWalkSpeed;
			}

		}
		if (KeyState(K_Down))
		{
			if (isOnOneWayPlatform) {
				pos.y += cOneWayPlatformThreshold;
				isOnOneWayPlatform = false;
				isThroughOneWay = true;
				mCurrentState = Jump;
			}

		}
		if ((Pressed(K_Jump)||Pressed(K_Attack)))
		{
			PlaySE(S_JUMP);
			nowJumpCnt += 1;
			speed.y = mJumpSpeed;
			mCurrentState = Jump;
			jumpFrame = 5;
			break;
		}
		else if (!isOnGround)
		{
			nowJumpCnt += 1;
			mCurrentState = Jump;
			break;
		}

		break;
	case Jump:



		if ((Pressed(K_Jump)||Pressed(K_Attack)) && nowJumpCnt < jumpCnt) {
			PlaySE(S_JUMP);
			nowJumpCnt += 1;
			speed.y = mJumpSpeed;
			jumpFrame = 30;
		}

		if (isOnOneWayPlatform) {
			isOnOneWayPlatform = false;
		}

		speed.y += GRV * DELTATIME;
		speed.y = MIN(speed.y, MAXFALLING);

		if (KeyState(K_Left) == KeyState(K_Right))
		{
			speed.x = 0.0f;
		}

		else if (KeyState(K_Right))
		{
			if (isPushesWallR) {
				speed.x = 0.0f;
			}
			else {
				speed.x = cMoveInAirMultiple * cWalkSpeed;
			}

		}
		else if (KeyState(K_Left))
		{
			if (isPushesWallL)
			{
				speed.x = 0.0f;
			}
			else {
				speed.x = -cMoveInAirMultiple * cWalkSpeed;
			}

		}

		if (!KeyState(K_Jump) && speed.y < 0.0f) {
			speed.y = MAX(speed.y, cMinJumpSpeed);
		}


		if (isOnGround) {
			nowJumpCnt = 0;
			if (KeyState(K_Right) == KeyState(K_Left))
			{
				mCurrentState = Stand;
				speed = MakeFloat2(0.0f, 0.0f);
			}
			else
			{
				mCurrentState = Walk;
				speed.y = 0.0f;
			}
		}



		break;
	}

	if (isCollisionToOther) {
		if (KeyState(K_Left)) {
			playerMoveState = PLRMOVLEFT;
		}
		if (KeyState(K_Right)) {
			playerMoveState = PLRMOVRIGHT;
		}
	}

	UpdatePhysics();

}

void Player::PlayerDraw() {


	float uNow, vNow;

	if (gameoverCnt > 0) {
		uNow = 0.0f;
		vNow = 3.0f*0.125f;
		DrawSpriteMove(texNo, oldPos.x, oldPos.y, uNow, vNow, 0.125f, 0.125f, texStaticScale.x, texStaticScale.y, playerMoveState);
		return;
	}

	if (respawnCnt > 0) {
		if (respawnCnt >= RESPAWNDEFCNT / 2) {
			uNow = 0.0f;
			vNow = 3.0f*0.125f;
			DrawSpriteMove(texNo, oldPos.x, oldPos.y, uNow, vNow, 0.125f, 0.125f, texStaticScale.x, texStaticScale.y, playerMoveState);
			return;
		}
		SetColor(255, 255, 255, 255 * ((respawnCnt % 2)));
	}
	else {
		SetColor(255, 255, 255, 255 );
	}





	switch (mCurrentState)
	{
	case Player::Stand:
	case Player::Walk:
		uNow = 0.125f * ((int)(GetFrame() / PAT_SPD) % MAX_PAT);
		vNow = 0.125f*mCurrentState;
		break;
	case Player::Jump:
		vNow = 0.125f*mCurrentState;
		if (nowJumpCnt == 1 && jumpFrame > 0) {
			uNow = 0.0f;
			jumpFrame -= 1;
			break;

		}
		if (nowJumpCnt == 2 && jumpFrame > 0) {

			uNow = 0.125f*(3.0f + (30 - jumpFrame) / 6);
			jumpFrame -= 1;
			break;

		}
		if (speed.y > 0) {
			uNow = 0.125f;
			jumpFrame -= 1;
		}
		if (speed.y <= 0) {
			uNow = 0.25f;
			jumpFrame -= 1;
		}
	}


	if (GetSceneIndex() == S_Title||GetSceneIndex() == S_GameOver) {
		DrawSpriteCircle(GetMapTexNo(), oldPos.x + texStaticScale.x*0.5f, oldPos.y + texStaticScale.y*0.5f, 0.0f, 4.0f*0.125f, 0.125f, 0.125f, texStaticScale.x * sinf(GetCircleCnt())*MAXCIRCLE, MAXCIRCLE*texStaticScale.y* sinf(GetCircleCnt()));

		DrawSpriteMove(texNo, oldPos.x, oldPos.y, uNow, vNow, 0.125f, 0.125f, texStaticScale.x, texStaticScale.y, playerMoveState);
	}
	else {
		Float2 drawPos = MakeFloat2(
			GameSystem::Lerp(oldPos.x, pos.x, 0.25f),
			GameSystem::Lerp(oldPos.y, pos.y, 0.25f));



		DrawSpriteCircle(GetMapTexNo(), drawPos.x + texStaticScale.x*0.5f, drawPos.y + texStaticScale.y*0.5f, 0.0f, 4.0f*0.125f, 0.125f, 0.125f, texStaticScale.x * sinf(GetCircleCnt())*MAXCIRCLE, MAXCIRCLE*texStaticScale.y* sinf(GetCircleCnt()));

		DrawSpriteMove(texNo, drawPos.x, drawPos.y, uNow, vNow, 0.125f, 0.125f, texStaticScale.x, texStaticScale.y, playerMoveState);

	}
	
}

void Player::AddRoomToPack(int index, int value)
{
	roomInPack[index] += value;

}

void Player::RespawnStart()
{
	respawnCnt = RESPAWNDEFCNT;
	isCollisionToOther = false;
	GameSystem::ShakeStart(15);
}

void Player::GameoverStart()
{
	gameoverCnt = RESPAWNDEFCNT;
	GameOver();
	isCollisionToOther = false;
	GameSystem::ShakeStart(15);
	StopBGM(5);

}

void Player::Reset()
{

	Float2 startSize = { 64.0f, 64.0f };
	Float2 startPos = BORNPOS;

	texStaticScale = startSize;

	isCollisionToOther = true;

	mAABB.center = startPos;
	pos = startPos;
	mAABB.halfScale = MakeFloat2(cHalfSizeX, cHalfSizeY);
	mAABBOffset = mAABB.halfScale;

	gameoverCnt = 0;
	respawnCnt = 0;	

	mJumpSpeed = cJumpSpeed;
	mWalkSpeed = cWalkSpeed;

	playerMoveState = PLRMOVLEFT;

	enable = true;

	playerMoveSpeed = PLRDEFSPD;

	for (int i = 0; i < 11; i++)
	{
		roomInPack[i] = 0;
	}

}

Player conPlr;





void InitPlayer(int condi)
{
	conPlr.SetPlayerTex(LoadTexture("rom:/chara.tga"));
	if (condi == S_Title) {
		conPlr.oldPos = BORNPOS;
		conPlr.pos = BORNPOS;
		conPlr.isCollisionToOther = true;
	}
	if (condi == S_Game){
		if (!isNowTutor()) {
			conPlr.AddRoomToPack(0,1);
			conPlr.AddRoomToPack(GameSystem::RandInt(1, 10), 1);
			conPlr.AddRoomToPack(GameSystem::RandInt(1, 10), 1);
			conPlr.AddRoomToPack(GameSystem::RandInt(1, 10), 1);
		}
}
}



void UninitPlayer()
{
	UnloadTexture(conPlr.texNo);
}


void UpdatePlayer()
{
	conPlr.PlayerUpdate();
}

void DrawPlayer()
{
	conPlr.PlayerDraw();
}

Player *GetActionPlayer() {
	return &conPlr;
}

void GetRoomInPack(int roomSent[11])
{
	for (int i = 0; i < 11; i++)
	{
		roomSent[i] = conPlr.GetRoomInPack(i);
	}

}

void SetRoomInPack(int index, int value) {
	conPlr.AddRoomToPack(index, value);
}

Float2 GetPlayerVelocity()
{
	return conPlr.GetVelocity();
}



int GetAllRoomCount() {
	int count = 0;
	for (int i = 0; i < 11; i++)
	{
		count += conPlr.GetRoomInPack(i);
	}
	return count;
}

void ResetPlayer()
{
	conPlr.Reset();
}

unsigned int GetPlayerTex() {
	return conPlr.GetPlayerTexNo();
}

