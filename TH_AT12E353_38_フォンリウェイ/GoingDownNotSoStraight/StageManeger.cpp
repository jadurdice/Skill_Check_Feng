
#include"StageManeger.h"
#include"Player.h"
#include"texture.h"
#include"Game.h"
#include"MapBank.h"
#include"KeyMap.h"
#include"Enemy.h"
#include"Effect.h"
#include"Logo.h"
#include"sound.h"

MapBluePrint titleMap =
{

	{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 5, 0,19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0, 5, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{10,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10 },
} };





float Stage::GetSwapCnt()
{
	return swapCnt;
}

void Stage::SetSwapCnt(float set)
{
	swapCnt = set;
}

float Stage::GetCircleCnt()
{
	return circleCnt;
}

MapBluePrint * Stage::GetNowRoom(int index)
{
	return &roomData[index];
}

void Stage::StageUpdate()
{
	if (isSwapping) {
		SwapPosLerpper();
	}
	if (isNext) {
		circleCnt += DEGREE_TO_RADIAN(1);
		if (circleCnt >= DEGREE_TO_RADIAN(90)) {
			circleCnt = DEGREE_TO_RADIAN(90);
			isNext = false;
			if (GetSceneIndex() == S_Title) {

				if (GetActionPlayer()->pos.x < SCREEN_WIDTH*0.5f) {
					SetTutor();
				}
				SceneChange(S_Game);


				return;
			}
			NextStage();
		}
	}
	else {
		if (circleCnt != DEGREE_TO_RADIAN(0)) {
			circleCnt -= DEGREE_TO_RADIAN(1);
			if (circleCnt <= DEGREE_TO_RADIAN(0)) {
				circleCnt = DEGREE_TO_RADIAN(0);
				GetActionPlayer()->isCollisionToOther = true;
				if (GetSceneIndex() == S_Title) {
				}
			}
		}
	}

	if (!isSwapping && !isNext&&GetActionPlayer()->isCollisionToOther&& nowFloor != 0) {

		if (stageTimer == (STAGETIMERDEF / 16)||
			stageTimer == (STAGETIMERDEF / 8)||
			stageTimer == (STAGETIMERDEF / 4)||
			stageTimer == (STAGETIMERDEF / 2)) {
			PlaySE(S_ENEMY);
		}

		if (stageTimer == 0 ) {
			stageTimer += ENEMYSPAWNINV;
			EnemySpawn();
		}
		stageTimer -= 1;

	}


}

void Stage::RoomSwapStart(int next)
{
	if (next != -1) {
		ClearEnemy();
		nextRoom = next;
		isSwapping = true;
		swapCnt = 0.0f;
		GetActionPlayer()->isCollisionToOther = false;
		Float2 playerNowPos = GetActionPlayer()->GetPlayerPos();

		if (playerNowPos.x < SCREEN_WIDTH*0.25f || playerNowPos.x > SCREEN_WIDTH*0.75f) {
			if (playerNowPos.x < SCREEN_WIDTH*0.25f) {
				swapPos.x = SWAPXRIGHT;

			}
			else {
				swapPos.x = SWAPXLEFT;
			}
			swapPos.y = playerNowPos.y;
		}
		else {
			if (playerNowPos.y < SCREEN_HEIGHT*0.25f) {
				swapPos.y = SWAPYDOWN;
			}
			else {
				swapPos.y = SWAPYUP;
			}
			swapPos.x = playerNowPos.x;
		}

	}
	else {
		nextRoom = nowRoomIndex;
		isSwapping = true;
		swapCnt = 0.0f;
	}
}

void Stage::SwapRoomData() {

	nowRoomIndex = nextRoom;
	nowRoom.LoadMap(roomData[nextRoom]);

	if (GetSceneIndex() == S_Title) {
		return;
	}

	//端をふさぎます
	if (nowRoomIndex / 3 == 0) {
		for (int i = 14; i < 18; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}
	}
	if (nowRoomIndex / 3 == 2) {
		for (int i = 14; i < 18; i++)
		{
			for (int j = 16; j < 18; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}
	}
	if (nowRoomIndex % 3 == 0) {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}
	}
	if (nowRoomIndex % 3 == 2) {
		for (int i = 30; i < 32; i++)
		{
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}
	}

	//通路確認
	if (!(roomData[nowRoomIndex].roomWay & WAYUP)) {
		for (int i = 14; i < 18; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}

	}
	if (!(roomData[nowRoomIndex].roomWay & WAYRIGHT)) {
		for (int i = 30; i < 32; i++)
		{
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}

	}
	if (!(roomData[nowRoomIndex].roomWay & WAYDOWN)) {
		for (int i = 14; i < 18; i++)
		{
			for (int j = 16; j < 18; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}

	}
	if (!(roomData[nowRoomIndex].roomWay & WAYLEFT)) {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][i] = Block;
			}
		}

	}

	//隣が存在かつ通路があるを確認
	//上チェック
	if (nowRoomIndex - 3 >= 0) {
		if (roomData[(nowRoomIndex - 3)].roomTag == R_Void) {
			for (int i = 14; i < 18; i++)
			{
				nowRoom.mTiles[0][i] = Block;
			}
		}
		else if (!(roomData[nowRoomIndex - 3].roomWay & WAYDOWN)) {
			for (int i = 14; i < 18; i++)
			{
				nowRoom.mTiles[0][i] = Block;
			}
		}
	}

	//左チェック
	if (nowRoomIndex % 3 != 0) {
		if (roomData[(nowRoomIndex - 1)].roomTag == R_Void) {
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][0] = Block;
			}
		}
		else if (!(roomData[nowRoomIndex - 1].roomWay & WAYRIGHT)) {
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][0] = Block;
			}
		}

	}

	//右チェック
	if (nowRoomIndex % 3 != 2) {
		if (roomData[(nowRoomIndex + 1)].roomTag == R_Void) {
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][31] = Block;
			}
		}
		else if (!(roomData[nowRoomIndex + 1].roomWay & WAYLEFT)) {
			for (int j = 7; j < 11; j++)
			{
				nowRoom.mTiles[j][31] = Block;
			}
		}


	}

	//下チェック
	if (nowRoomIndex + 3 < 9) {
		if (roomData[(nowRoomIndex + 3)].roomTag == R_Void) {
			for (int i = 14; i < 18; i++)
			{
				nowRoom.mTiles[17][i] = Block;
			}
		}
		else if (!(roomData[nowRoomIndex + 3].roomWay & WAYUP)) {
			for (int i = 14; i < 18; i++)
			{
				nowRoom.mTiles[17][i] = Block;
			}
		}

	}

	if (isNowTutor() && nowRoomIndex == 8) {
		EnemySpawnTutor();
	}

}

int Stage::NextRoomCheck(int dir) {
	switch (dir) {
	case GoUp:
		if (nowRoomIndex / 3 != 0) {
			return nowRoomIndex - 3;
		}
		break;
	case GoRight:
		if (nowRoomIndex % 3 != 2) {
			return nowRoomIndex + 1;
		}
		break;
	case GoLeft:
		if (nowRoomIndex % 3 != 0) {
			return nowRoomIndex - 1;
		}
		break;
	case GoDown:
		if (nowRoomIndex / 3 != 2) {
			return nowRoomIndex + 3;
		}
		break;
	}
	return -1;
}

void Stage::SwapPosLerpper()
{
	if (GetSceneIndex() == S_Title) {
		swapCnt += 0.005f;
	}
	else {
		swapCnt += 0.015f;
	}

	if (swapCnt >= 1.0f) {
		swapCnt = 1.0f;
		GetActionPlayer()->isCollisionToOther = true;
		isSwapping = false;
	}

	if (isOver) {
		return;
	}

	Float2 playerNowPos = GetActionPlayer()->GetPlayerPos();

	Float2 nextPos = MakeFloat2(
		GameSystem::Lerp(playerNowPos.x, swapPos.x, swapCnt),
		GameSystem::Lerp(playerNowPos.y, swapPos.y, swapCnt));

	GetActionPlayer()->SetPlayerPos(nextPos);




}

void Stage::SetRoomInStage(MapBluePrint newRoom, int location)
{
	roomData[location] = newRoom;
	stageTimer += ONEROOMTIME;
}


int Stage::GetNowGridInfo(Float2 pos) {
	int gridX = nowRoom.GetMapTileXAtPoint(pos.x);
	int gridY = nowRoom.GetMapTileYAtPoint(pos.y);

	return nowRoom.GetTile(gridX, gridY);

}

void Stage::NextStageStart()
{
	isNext = true;
	GetActionPlayer()->isCollisionToOther = false;
	ClearEnemy();
}



void Stage::OpenBox(Float2 plrPos) {
	int x, y;

	x = nowRoom.GetMapTileXAtPoint(plrPos.x);
	y = nowRoom.GetMapTileYAtPoint(plrPos.y);
	roomData[nowRoomIndex].chunkData[y][x] = OpenedBox;
	SwapRoomData();
}

void Stage::GameOver()
{
	swapCnt = 0.0f;
	isSwapping = true;
	isOver = true;
}

void Stage::Title()
{
	for (int i = 0; i < 9; i++)
	{
		roomData[i] = titleMap;
		roomData[i].roomTag = R_Void;
	}

	nowFloor = 0;
	swapPos = BORNPOS;
	RoomSwapStart(-1);
	nowRoom.LoadMap(titleMap);
	swapCnt = 0.5f;

}

int Stage::GetNowFloor()
{
	return nowFloor;
}

void Stage::Reset()
{
	 nextRoom = 0;

	 nowFloor = 0;
	 goalLocation = 0;
	 isSwapping = false;
	 isNext = false;
	 isOver = false;
	 circleCnt = 0.5f;
	swapPos = MakeFloat2( 0.0f,0.0f );
	for (int i = 0; i < 9; i++)
	{
		BluePrintClear(roomData[i]);
	}

}



void Stage::NextStage()
{
	nowRoom.ClearRoom();

	for (int i = 0; i < 9; i++)
	{
		BluePrintClear(roomData[i]);
	}

	if (GetPlayingId() == 0x01000000) {
		StopBGM(5);
		PlayBGM(B_PLAY);
	}
	
		nowFloor += 1;
		swapPos = BORNPOS;


	int startRoom = GameSystem::RandInt(0, 8);
	do {
		goalLocation = GameSystem::RandInt(0, 8);
	} while (
		startRoom == goalLocation ||
		startRoom == goalLocation - 1 ||
		startRoom == goalLocation + 1 ||
		startRoom == goalLocation - 3 ||
		startRoom == goalLocation + 3);

	nowRoomIndex = startRoom;
	nextRoom = startRoom;

	SetRoomInStage(GetStartRoom(), startRoom);
	SetRoomInStage(GetGoalRoom(goalLocation), goalLocation);

	nowRoom.LoadMap(roomData[nowRoomIndex]);

	SwapRoomData();

	stageTimer = STAGETIMERDEF;

}

void Stage::PrepareTutorStage() {
	nowRoom.ClearRoom();
	GetTutorRoom(roomData);
	nowRoomIndex = 6;
	nextRoom = 6;
	nowRoom.LoadMap(roomData[nowRoomIndex]);
	SwapRoomData();
}


int condition;
Stage runStage;
unsigned int tileTexNo;

void InitStageMap(int condi) {
	tileTexNo = LoadTexture(MAPTEXTUREPATH);
	runStage.nowRoom.SetTileTex(tileTexNo);
	SetMapEffectTex(tileTexNo);


	if (condi == S_Title) {
		runStage.Title();
	}
	else if (isNowTutor()) {
		runStage.PrepareTutorStage();
	}
	else {
		runStage.NextStage();
		runStage.swapPos = BORNPOS;
		runStage.RoomSwapStart(-1);


	}

}
void UninitStageMap() {
	UnloadTexture(tileTexNo);
}
void UpdateStageMap() {
	runStage.StageUpdate();
}
void DrawStageMap() {
	runStage.nowRoom.DrawMap();
}

TileMap *GetGameMap() {
	return &runStage.nowRoom;
}



bool SwapDetected(int dir) {
	//端チェック
	int next = runStage.NextRoomCheck(dir);
	//部屋移動開始
	if (next != -1) {
		runStage.RoomSwapStart(next);
		PlaySE(S_LADDER);
		return false;
	}
	return true;
}

void SwapRoomData() {
	runStage.SwapRoomData();
}

float GetSwapCnt()
{
	return runStage.GetSwapCnt();
}

float GetCircleCnt() {
	return runStage.GetCircleCnt();
}

int GetMapTexNo()
{
	return runStage.nowRoom.texNo;
}

MapBluePrint* GetNowRoom(int roomIndex) {
	return runStage.GetNowRoom(roomIndex);
}

int GetPlayerRoom() {
	return runStage.nowRoomIndex;

}

void SetRoomInStage(MapBluePrint newRoom, int location) {
	runStage.SetRoomInStage(newRoom, location);
}

void NextStage() {
	runStage.NextStageStart();
	PlaySE(S_LADDER);
}

int GetNowGridInfo(Float2 pos) {
	return runStage.GetNowGridInfo(pos);
}
int GetNowFloor() {
	return runStage.GetNowFloor();
}

void GetNewRoomToPack() {
	Float2 plrPos = GetActionPlayer()->GetPlayerPos();

	runStage.OpenBox(plrPos);

	if (isNowTutor()) {
		SetRoomInPack(0, 1);
		SetMapEffect(plrPos, &GetActionPlayer()->mAABB.center, 0);
		return;
	}


	runStage.OpenBox(plrPos);
	int index;
	int temp = GameSystem::RandInt(0, 99);
	if (temp < 60) {
		temp = GameSystem::RandInt(0, 5);
		index = R_UR + temp;
	}
	else if (temp >= 60 && temp < 85) {
		temp = GameSystem::RandInt(0, 3);
		index = R_URL + temp;
	}
	else {
		index = R_URLD;
	}

	SetRoomInPack(index, 1);
	SetMapEffect(plrPos, &GetActionPlayer()->mAABB.center, index);

}

void RespawnStart() {
	GetActionPlayer()->RespawnStart();
	PlaySE(S_DAMAGE);
}



void Respawn() {
	runStage.RoomSwapStart(-1);
}

void GameOver() {
	runStage.GameOver();
}

void ResetStage()
{
	runStage.Reset();
}