#pragma once


#include"MapObject.h"

#define SWAPYUP		(30.0f)
#define SWAPYDOWN	(923.0f)
#define SWAPXLEFT	(25.0f)
#define SWAPXRIGHT	(1870.0f)

#define STAGETIMERDEF	(60*30)
#define	ONEROOMTIME		(60*5)
#define ENEMYSPAWNINV	(60*5)

enum SwapDirection{
	GoUp,
	GoRight,
	GoLeft,
	GoDown
};



class Stage
{


	

public:

	TileMap nowRoom;
	int nowRoomIndex;

	float GetSwapCnt();
	void SetSwapCnt(float set);
	float GetCircleCnt();
	MapBluePrint* GetNowRoom(int index);

	void StageUpdate();
	int NextRoomCheck(int dir);
	void RoomSwapStart(int next);
	void SwapRoomData();
	void SwapPosLerpper();
	void SetRoomInStage(MapBluePrint newRoom, int location);
	int GetNowGridInfo(Float2 pos);
	void NextStageStart();
	void NextStage();
	void OpenBox(Float2 plrPos);
	void GameOverStart();
	void GameOver();
	void Title();
	void PrepareTutorStage();
	int GetNowFloor();
	Float2 swapPos;

	void Reset();

private:
	
	int stageTimer;

	MapBluePrint	roomData[9];
	int nextRoom;

	int nowFloor;
	int goalLocation;
	bool isSwapping;
	bool isNext;
	bool isOver;
	float swapCnt;
	float circleCnt;

	Float2 forcePos;
};

void InitStageMap(int condi);
void UninitStageMap();
void UpdateStageMap();
void DrawStageMap();
TileMap *GetGameMap();

bool SwapDetected(int dir);
void SwapRoomData();
float GetSwapCnt();
float GetCircleCnt();
int GetMapTexNo();
MapBluePrint* GetNowRoom(int roomIndex);
int GetPlayerRoom();
void SetRoomInStage(MapBluePrint newRoom, int location);
void NextStage();
int GetNowGridInfo(Float2 pos);
void GetNewRoomToPack();
void GameOver();
int GetNowFloor();

void Respawn();
void RespawnStart();

void ResetStage();