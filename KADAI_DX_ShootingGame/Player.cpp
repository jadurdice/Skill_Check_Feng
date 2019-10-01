
#include"Player.h"
#include"Effect.h"
#include"Enemy.h"
#include"Game.h"
#include"Item.h"
#include"Bullet.h"
#include"common.h"
#include"Debug.h"
#include"sound.h"
#include"continue.h"
#include"SceneManeger.h"
#include"GameMaster.h"
#include"PhaseManeger.h"
#include"Particle.h"

D3DXVECTOR2 temp;

void Player::PlayerInit() {

	D3DXVECTOR2 startSize = { PLRTEXW, PLRTEXH };
	D3DXVECTOR2 startPos = { SCREEN_WIDTH*-0.1f, SCREEN_HEIGHT*0.45f };

	SetPlayerPos(startPos);
	SetPlayerScale(startSize);

	playerTexNo = TextureSetLoadFile("asset/texture/object.png", 782, 782);

	shootInv = 10;
	enable = false;
	power = 10;

	respawnCnt = 500;

	stageEnd = false;

	playerCol.pos = startPos;
	playerCol.radius = 8;

	playerMoveSpeed = PLRDEFSPD;
	barrelAngle = -90.0f;

	missileMax = MISSILEMAXDEF;
	missileNow = missileMax;
	missileInverse = MISSILEINVDEF;
	

	inputPossible = true;

	life = 3;
}

CircleCol * Player::GetCollision()
{
	return &playerCol;
}

int Player::GetPower()
{
	return (1+(power/10));
}

int Player::GetRawPower()
{
	return power;
}

void Player::SetPower(int addNum)
{
	power += addNum;
}

int Player::GetLife()
{
	return life;
}

void Player::SetLife(int addNum)
{
	life += addNum;
}

unsigned int Player::GetPlayerTexNo() {
	return playerTexNo;
}

D3DXVECTOR2 Player::GetPlayerPos() {
	return playerCol.pos;
}

D3DXVECTOR2 Player::GetPlayerScale() {
	return playerScale;
}

void Player::SetPlayerTex(unsigned int texNo) {
	playerTexNo = texNo;
}

void Player::SetPlayerVelocity(D3DXVECTOR2 velocity) {
	playerVelocity.x += velocity.x;
	playerVelocity.y += velocity.y;
}

void Player::SetPlayerPos(D3DXVECTOR2 pos) {
	playerPos = pos;
}

void Player::SetPlayerScale(D3DXVECTOR2 scale) {
	playerScale.x = scale.x*SIZEADJUST;
	playerScale.y = scale.y*SIZEADJUST;

	texStaticScale = scale;
}


void Player::PlayerInput() {

	if (!inputPossible) {
		return;
	}

		playerVelocity = { 0.0f,0.0f };

	if (Keyboard_IsPress(DIK_A) && !Keyboard_IsPress(DIK_D)) {
		playerVelocity.x -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_D) && !Keyboard_IsPress(DIK_A)) {
		playerVelocity.x += 1.0f;
	}
	if (Keyboard_IsPress(DIK_W) && !Keyboard_IsPress(DIK_S)) {
		playerVelocity.y -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_S) && !Keyboard_IsPress(DIK_W)) {
		playerVelocity.y += 1.0f;
	}
	if (Keyboard_IsPress(DIK_J)) {
		barrelAngle -= ROTSPD;
	}
	if (Keyboard_IsPress(DIK_L)) {
		barrelAngle += ROTSPD;
	}

	if (Keyboard_IsTrigger(DIK_SPACE)) {
		if (missileNow > 0) {
			isShootMissile = true;
			lastMissileCnt = missileNow;
		}
	}


	if (Keyboard_IsPress(DIK_P)) {
		SetMissile(10);
	}
	if (Keyboard_IsTrigger(DIK_E) && Keyboard_IsPress(DIK_LSHIFT)) {
		FwdPhase();
	}
	if (Keyboard_IsPress(DIK_O)) {
		power += 10;
	}

	if (!Keyboard_IsPress(DIK_LSHIFT)) {
		playerMoveSpeed = PLRDEFSPD;
	}
	else {
		playerMoveSpeed = PLRDEFSPD * 0.5f;
	}

	if (Keyboard_IsPress(DIK_K)) {
		if (lastShoot <= 0) {
			BulletCreate(muzzlePos.x, muzzlePos.y, (barrelAngle + 90.0f), 10.0f, PLR);
			SetParticle(P_Muzzle, muzzlePos, D3DCOLOR_RGBA(255, 128, 50, 255), 5, 0.2f, barrelAngle+180);

			if (power > 10) {
				D3DXVECTOR2 temp;
				temp = {
					muzzlePos.x + cosf(DEGREE_TO_RADIAN(barrelAngle+90.0f)),
					muzzlePos.y + sinf(DEGREE_TO_RADIAN(barrelAngle+90.0f))
				};
				int powerTemp = (power/10);
				WayBulletCreate(muzzlePos, temp , ((powerTemp)+1), (powerTemp*10), 10.0f, PLR);
			}


			lastShoot += shootInv;
			PlaySound(SE_MACHINEGUN);
		}
	}


}


void Player::MovePlayer() {

	playerAngle = playerVelocity.y * 50.0f;
	playerOldAngle = GameSystem::Lerp(playerOldAngle, playerAngle, 0.075f);

	D3DXVec2Normalize(&playerVelocity, &playerVelocity);
	D3DXVECTOR2 playerMove = playerVelocity * playerMoveSpeed;
	playerPos += playerMove;
	playerAngle *= DRAG * 1.5f;

	if (stageEnd) {

		if (playerPos.x > BORDERRIGHT)
		{
			StopSound(SE_BOSS2SURROUND);
			SetScene(S_GameOver);
			playerPos.x = SCREEN_WIDTH * -5.0f;
		}
		else {
			playerPos.x = GameSystem::Lerp(playerPos.x, SCREEN_WIDTH*1.2f, 1.5f*DELTATIME);
		}
		return;
	}


	if (playerPos.x + playerMove.x < BORDERLEFT)
	{
		if (respawnCnt <= (RESPAWNDEF) / 3) {
			playerPos.x = BORDERLEFT;
		}
	}
	else if (playerPos.x + playerMove.x + playerScale.x > BORDERRIGHT)
	{
		playerPos.x = BORDERRIGHT - playerScale.x;
	}
	//else 
	//{
	//	playerPos.x += cos(DEGREE_TO_RADIAN(playerOldAngle)) * playerMove.x;
	//}

	if (playerPos.y + playerMove.y < BORDERUP)
	{
		playerPos.y = BORDERUP;
	}
	else if (playerPos.y + playerMove.y + playerScale.y > BORDERDOWN)
	{
		playerPos.y = BORDERDOWN - playerScale.y;
	}
	//else 
	//{
	//	playerPos.y += sin(DEGREE_TO_RADIAN(playerOldAngle)) * playerMove.y;
	//}

}

void Player::DamegeCheck()
{
	for (int i = 0; i < ENEMY_CNT_MAX; i++)
	{
		if (!GetEnemy(i)->GetEnemyEnable()) {
			continue;
		}
		checkEnemy2Player(this, GetEnemy(i));
	}

	if (GetBoss()->GetEnemyEnable() && GetBoss()->hitPoint > 0) {
		checkEnemy2Player(this, GetBoss());
	}

	for (int j = 0; j < B_Count; j++)
	{
		for (int i = 0; i < GetBulletMax(); i++)
		{
			if (!GetBullet(j, i)->GetBulletEnable() || GetBullet(j, i)->shootBy != ENM) {
				continue;
			}
			checkBullet2Player(GetBullet(j, i), this);
		}
	}

}

void Player::ItemCheck()
{
	for (int i = 0; i < ITEMMAX; i++)
	{
		if (!GetItem(i)->GetItemEnable()) {
			continue;
		}
		checkItem2Player(GetItem(i),this);
	}
}


void Player::PlayerDestroy()
{
	life -= 1;
	SetEffect(playerCol.pos);
	enable = false;
	playerPos = { -3.0f*PLRTEXW,0.45f*SCREEN_HEIGHT };
	respawnCnt = RESPAWNDEF;
	inputPossible = false;
	power = max(10,power * 0.5f);
	missileNow = missileMax;
	missileCnt = 0;
	isShootMissile = false;
	GameSystem::ShakeStart(60,5.0f);
	ClearBullet();

	if (GetPhaseCnt() > 10) {
		for (int i = 0; i < 4; i++)
		{
			ItemCreate({SCREEN_WIDTH,SCREEN_HEIGHT*(0.2f*(i+1))}, I_Power);
		}
	}




}

void Player::PlayerUpdate() {

	if (respawnCnt > 0 ) {
		respawnCnt -= 1;
		if (life == 0 && respawnCnt == (RESPAWNDEF*(4.0f/6.0f))) {
			SetConti();
		}

		if (respawnCnt == (RESPAWNDEF) / 3) {
			StopSound(SE_BOSS2SURROUND);
			inputPossible = true;
		}
		if (respawnCnt < (RESPAWNDEF * 2) / 3 && respawnCnt >(RESPAWNDEF) / 3) {

			if (life == 0) {
				return;
			}

			if(respawnCnt == (RESPAWNDEF * 2) / 3){
				PlaySound(SE_BOSS2SURROUND);
			}

			enable = true;
			playerPos = { GameSystem::Lerp(playerPos.x, SCREEN_WIDTH*0.1f,DELTATIME),0.45f*SCREEN_HEIGHT };
			playerOldAngle = 0.0f;

		}

	}



	if (!enable) {
		return;
	}

	

	PlayerInput();
	MovePlayer();

	if (respawnCnt <= 0 && !isShootMissile) {
		DamegeCheck();
	}

	ShootMissile();
	ItemCheck();

	brlPos = {
	playerPos.x + 0.25f*PLRTEXW,
	playerPos.y + 0.5f*PLRTEXH
	};

	muzzlePos = {

		brlPos.x+ 10.0f  - (BRLTEXH * SIZEADJUST) * sinf(DEGREE_TO_RADIAN(barrelAngle)),
		brlPos.y  + (BRLTEXH * SIZEADJUST) * cosf(DEGREE_TO_RADIAN(barrelAngle))
	};

	playerCol.pos = { brlPos.x + 0.25f*PLRTEXW , brlPos.y };

	frameCnt = GameSystem::GetFrame();

	if (frameCnt % 10 == 0) {
		SetParticle(P_Dust, {
			playerPos.x + GameSystem::RandFloat(-2.0f,2.0f),
			playerPos.y + playerScale.y*0.6f + GameSystem::RandFloat(-2.0f,2.0f) }
		, 0, 128, 0.5f, 0.0f);
	}

	if (lastShoot > 0) {
		lastShoot -= 1;
	}
}

void Player::PlayerDraw() {

	if (enable) {

		DebugFont_Draw(SCREEN_WIDTH*0.9f,SCREEN_HEIGHT*0.9f,"%d",missileCnt);
		DebugSetColor(D3DCOLOR_RGBA(0, 0, 255, 255));
		DebugDrawCircleCol(playerCol.pos.x, playerCol.pos.y, playerCol.radius);
		CircleCol tempCol = playerCol;
		tempCol.radius *= 3.5f;
		DebugSetColor(D3DCOLOR_RGBA(0, 255, 255, 255));
		DebugDrawCircleCol(tempCol.pos.x, tempCol.pos.y, tempCol.radius);


		if ((respawnCnt / 2) % 3 == 1) {
			SetColor(255, 255, 255, 0);
		}

		DrawSpriteRotPlg(
			playerTexNo,
			playerPos.x, playerPos.y,
			PLRTEXU, PLRTEXV,
			PLRTEXW, PLRTEXH,
			playerOldAngle - 90.0f,
			0.5f, 0.5f,
			SIZEADJUST, SIZEADJUST
		);



		DrawSpriteRotPlg(
			playerTexNo,
			brlPos.x, brlPos.y,

			BRLTEXU, BRLTEXV,
			BRLTEXW, BRLTEXH,
			barrelAngle,
			0.5f, 0.0f,
			SIZEADJUST, SIZEADJUST
		);

		SetColor(255, 255, 255, 255);
	}
}

void Player::ShootMissile()
{
	if (!isShootMissile) {
		if (missileNow == missileMax) {
			return;
		}

		if (missileCnt >= missileInverse) {
			if (missileNow < missileMax) {
				missileNow += 1;
			}
			missileCnt = 0;
		}		
	}
	else {
		if (missileNow == 0) {

			int penality;

			float pena = 1.0f - ((float)lastMissileCnt / (float)missileMax);

			penality = pena  * MISSILEINVDEF;
			
			missileCnt = -1 * MISSILEINVDEF + penality;
			isShootMissile = false;
			return;
		}
		if (missileCnt % MISSILEPERFRAME == 0) {
			D3DXVECTOR2 * target;
			if (GetEnableEnemy()) {
				target = &GetNearestEnemy()->GetCollision()->pos;
				HomingCreate(brlPos, target, 120, 0, 1.0f, PLR);
				missileNow -= 1;
				missileCnt = 0;
			}
			else if (GetNearestBullet()) {
				target = GetNearestBullet();
				HomingCreate(brlPos, target, 120, 0, 1.0f, PLR);
				missileNow -= 1;
				missileCnt = 0;

			}
			else {
				missileCnt = 0;
				isShootMissile = false;
			}
		}
	}
	missileCnt += 1;
}

int Player::GetMissileNow()
{
	return missileNow;
}

int Player::GetMissileMax()
{
	return missileMax;
}

void Player::SetMissile(int addNum)
{
	missileMax += addNum;
	missileNow = missileMax;
}

Player conPlr;





void InitPlayer()
{
	conPlr.PlayerInit();
}



void UninitPlayer()
{

}


void UpdatePlayer()
{
	conPlr.PlayerUpdate();
	temp = { SCREEN_WIDTH*0.5f + SCREEN_WIDTH * 0.25f *sinf(DEGREE_TO_RADIAN(GameSystem::GetFrame())),0.0f };

}

void DrawPlayer()
{
	conPlr.PlayerDraw();
}

Player *GetActionPlayer() {
	return &conPlr;
}

int GetPlayerTex() {
	return conPlr.playerTexNo;
}